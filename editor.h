#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>
#include <QMimeData>
#include <QKeyEvent>
#include <QTime>
#include "settings.h"

class Editor : public QTextEdit
{
	Q_OBJECT
public:
	Editor(QWidget* parent=0);
	Settings* s;
	QTime lastEditTime;
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *e);
public slots:
	void insertFromMimeData(const QMimeData *source);
};

#endif // EDITOR_H
