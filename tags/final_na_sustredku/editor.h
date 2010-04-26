#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QTextEdit>
#include <QMimeData>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <QQueue>
#include <QDebug>
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
	QQueue<QString> klavesy;
signals:
	void keystroke();
public slots:
	void insertFromMimeData(const QMimeData *source);
	void delayedKey();
};

class InputEditor : public QPlainTextEdit
{
	Q_OBJECT
public:
	InputEditor(QWidget* parent=0);
	QMimeData* createMimeDataFromSelection() const;

};

#endif // EDITOR_H
