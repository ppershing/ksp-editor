#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProcess>
#include <QTimer>
#include "settings.h"
#include "shopdialog.h"
#include "kupondialog.h"
#include "testdialog.h"
#include "editor.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void show();
public slots:
	void help();
	void reload();
	void submit();
	void godmode();
	void positionChanged();
	void clearText();
	void checkIdle();
protected:
    void changeEvent(QEvent *e);
	void resizeEvent(QResizeEvent *e);
	void customResize();
	void updateStatusBar();
	Settings* s;

private:
    Ui::MainWindow *ui;
	ShopDialog* shopDialog;
	KuponDialog* kuponDialog;
	TestDialog* testDialog;
	QTime lastEditTime;
};

#endif // MAINWINDOW_H
