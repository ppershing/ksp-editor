#include "editor.h"

Editor::Editor(QWidget* parent) : QTextEdit(parent)
{
}

void Editor::insertFromMimeData(const QMimeData *source){
	if(s->getBool("interaction/canPaste"))
		QTextEdit::insertFromMimeData(source);
}
