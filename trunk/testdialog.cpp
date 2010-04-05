#include "testdialog.h"
#include "ui_testdialog.h"

TestDialog::TestDialog(Settings* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);
	s = settings;
}

TestDialog::~TestDialog()
{
    delete ui;
	delete testProcess;
}

void TestDialog::show(){
	ui->textBrowser->clear();
	ui->textBrowser->append("testing...");
	QDialog::show();
	testProcess = new QProcess();
	connect(testProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(testFinished(int,QProcess::ExitStatus)));
	connect(testProcess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(error(QProcess::ProcessError)));
	QFile file("file.cpp");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		ui->textBrowser->append("problem with creating temporary file");
	file.write(program.toAscii());
	file.close();
	testProcess->setStandardInputFile("file.cpp");
	testProcess->start(s->getString("paths/testovac"), QStringList());
}

void TestDialog::error(QProcess::ProcessError e){
	ui->textBrowser->append("error");
	if(e==QProcess::FailedToStart)ui->textBrowser->append("failed to start testing");
}

void TestDialog::testFinished(int exitCode, QProcess::ExitStatus exitStatus){
	if(exitStatus!=QProcess::NormalExit){
		ui->textBrowser->append("problem s testovacom");
	}else{
		QString output = testProcess->readAllStandardOutput();
		ui->textBrowser->append(output + QString("otestovane: ") + QString::number(exitCode));
	}
}

void TestDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
