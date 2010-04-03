#include "editor.h"

Editor::Editor(QWidget* parent) : QTextEdit(parent)
{
}

void Editor::keyPressEvent(QKeyEvent *e){
	if(e->key()==Qt::Key_Backspace && !s->getBool("interaction/backspace"))return;
	QTextEdit::keyPressEvent(e);
}

void Editor::insertFromMimeData(const QMimeData *source){
	if(s->getBool("interaction/canPaste"))
		QTextEdit::insertFromMimeData(source);
}
