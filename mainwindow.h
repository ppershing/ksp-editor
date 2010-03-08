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
protected:
    void changeEvent(QEvent *e);
	Settings* s;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
