#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>
#include <QMimeData>
#include "settings.h"

class Editor : public QTextEdit
{
	Q_OBJECT
public:
	Editor(QWidget* parent=0);
	Settings* s;
public slots:
	void insertFromMimeData(const QMimeData *source);
};

#endif // EDITOR_H
