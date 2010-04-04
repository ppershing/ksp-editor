#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>
#include <QMimeData>
#include <QKeyEvent>
#include "settings.h"

class Editor : public QTextEdit
{
	Q_OBJECT
public:
	Editor(QWidget* parent=0);
	Settings* s;
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *e);
public slots:
	void insertFromMimeData(const QMimeData *source);
};

#endif // EDITOR_H
