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

protected:
    void changeEvent(QEvent *e);
	Settings* s;

private:
    Ui::MainWindow *ui;

private slots:
	void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
