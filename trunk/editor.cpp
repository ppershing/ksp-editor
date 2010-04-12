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
	QTextEdit::keyPressEvent(e);
	lastEditTime = QTime::currentTime();
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
