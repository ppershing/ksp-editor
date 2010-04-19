#include <QApplication>
#include <QClipboard>
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
	if(s->getBool("upgrades/readOnly"))return;
	bool isText=e->text().at(0).isPrint();
	isText |= (e->key()==Qt::Key_Return);
	isText |= (e->key()==Qt::Key_Space);
	//qDebug() << "key code: " << e->key();
	if(!isText){
		qDebug("not text");
		if(e->key()==Qt::Key_Backspace){
			if(!s->getBool("upgrades/backspace"))return;
			textCursor().deletePreviousChar();
		}
		if(e->key()==Qt::Key_Delete){
			if(!s->getBool("upgrades/backspace"))return;
			textCursor().deleteChar();
		}
		if(e->key()==90){ //Ctrl-Z
			if(!s->getBool("upgrades/undoRedo"))return;
			this->undo();
		}
		if(e->key()==82){ //Ctrl-R
			if(!s->getBool("upgrades/undoRedo"))return;
			this->redo();
		}
		if(e->key()==67){ //Ctrl-C
			if(!s->getBool("upgrades/paste"))return;
			this->copy();
		}
		if(e->key()==86){ //Ctrl-V
			if(!s->getBool("upgrades/paste"))return;
			qDebug() << QApplication::clipboard()->text();
			this->insertPlainText(QApplication::clipboard()->text());
		}
		QTextEdit::keyPressEvent(e);
	}else{
		int pos = klavesy.length();
		if(!s->getBool("upgrades/synchronize"))
			pos = rand() % (klavesy.length()+1);
		klavesy.insert(pos,e->text());
		int delay = s->getInt("screensaver/delay0");
		if(s->getBool("upgrades/delay1"))delay = s->getInt("screensaver/delay1");
		if(s->getBool("upgrades/delay2"))delay = s->getInt("screensaver/delay2");
		QTimer::singleShot(delay,this,SLOT(delayedKey()));
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
