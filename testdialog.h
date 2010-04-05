#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include <QProcess>
#include <QFile>
#include <QDebug>
#include "settings.h"

namespace Ui {
    class TestDialog;
}

class TestDialog : public QDialog {
    Q_OBJECT
public:
	TestDialog(Settings* settings, QWidget *parent = 0);
    ~TestDialog();

	QString program;

public slots:
	void show();
	void error(QProcess::ProcessError e);
	void testFinished(int exitCode,QProcess::ExitStatus exitStatus);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TestDialog *ui;
	Settings* s;
	QProcess* testProcess;
};

#endif // TESTDIALOG_H
