#include "editor.h"

Editor::Editor(QWidget* parent) : QTextEdit(parent)
{
}

void Editor::keyPressEvent(QKeyEvent *e){
	if(s->getInt("prices/keyStroke")>s->getInt("credits/count"))return;
	s->decrement("credits/count",s->getInt("prices/keyStroke"));
	emit keystroke();
	if(e->key()==Qt::Key_Backspace && !s->getBool("upgrades/backspace"))return;
	if((e->key()==Qt::Key_PageUp || e->key()==Qt::Key_PageDown) && !s->getBool("upgrades/pageUpDown"))return;
	if(e->text().length()==0)
		QTextEdit::keyPressEvent(e);
	else{

		//napad: mozem zahadzovat ked je vela klaves naraz

		klavesy.enqueue(e->text());
		QTimer::singleShot(3000 - 1500*s->getInt("upgrades/delay1")-1000*s->getInt("upgrades/delay2")-500*s->getInt("upgrades/delay3"),this,SLOT(delayedKey()));
	}
	lastEditTime = QTime::currentTime();
}

void Editor::delayedKey(){
	qDebug() << klavesy.length();
	if(klavesy.isEmpty())return;
	qDebug() << "not empty";
	qDebug() << klavesy.head();
	insertPlainText(klavesy.dequeue());
}

void Editor::mousePressEvent(QMouseEvent *e){
	if(!s->getBool("upgrades/mouseInteraction"))return;
	QTextEdit::mousePressEvent(e);
}

void Editor::insertFromMimeData(const QMimeData *source){
	if(s->getBool("upgrades/paste"))
		QTextEdit::insertFromMimeData(source);
}

InputEditor::InputEditor(QWidget *parent) : QPlainTextEdit(parent)
{
}


QMimeData* InputEditor::createMimeDataFromSelection() const{
	QMimeData* m = new QMimeData();
	m->text() = "";
	return m;
}
