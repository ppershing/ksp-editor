#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "settings.h"

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
	void reload();
	void submit();
	void godmode();
	void positionChanged();
protected:
    void changeEvent(QEvent *e);
	void resizeEvent(QResizeEvent *e);
	void customResize();
	void updateStatus();
	Settings* s;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
