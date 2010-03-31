#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	s = new Settings();
	shopDialog = new ShopDialog(s);
	kuponDialog = new KuponDialog();
	QShortcut* f1 = new QShortcut( Qt::Key_F1, this );
	connect(f1,SIGNAL(activated()),this,SLOT(help()));
	QShortcut* f5 = new QShortcut( Qt::Key_F5, this );
	connect(f5,SIGNAL(activated()),this,SLOT(reload()));
	QShortcut* f6 = new QShortcut( Qt::Key_F6, this );
	connect(f6,SIGNAL(activated()),this,SLOT(submit()));
	QShortcut* f7 = new QShortcut( Qt::Key_F7, this );
	connect(f7,SIGNAL(activated()),shopDialog,SLOT(show()));
	QShortcut* f8 = new QShortcut( Qt::Key_F8, this );
	connect(f8,SIGNAL(activated()),kuponDialog,SLOT(show()));
	QShortcut* tazb = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_T,Qt::CTRL+Qt::Key_A,Qt::CTRL+Qt::Key_Z,Qt::CTRL+Qt::Key_B), this );
	connect(tazb,SIGNAL(activated()),this,SLOT(godmode()));

	connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(positionChanged()));

}

MainWindow::~MainWindow()
{
    delete ui;
	delete shopDialog;
	delete kuponDialog;
	delete s;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::resizeEvent(QResizeEvent *e){
	customResize();
}

void MainWindow::customResize(){
	ui->textEdit->resize(this->width(),this->height()-(20*s->getProp("statusbar/enabled").toInt()));
}

void MainWindow::show(){
	this->reload();
	QMainWindow::show();
}

void MainWindow::help(){
	QMessageBox::information(0,"Help","F1: Help\nF5: Reload\nF6: Submit\nF7: Shop\nF8: Pouzi kupon");
}

void MainWindow::reload(){
	s->load();

	// FONT

	QFont f = ui->textEdit->document()->defaultFont();
	f.setPointSize(s->getProp("font/size").toInt());
	f.setWordSpacing(s->getProp("font/word_spacing").toInt());
	f.setFamily(s->getProp("font/family").toString());
	// tu sa doplnia dalsie nastavenia fontu
	ui->textEdit->document()->setDefaultFont(f);

	//INTERACTION

	QFlags<Qt::TextInteractionFlag> flags = Qt::NoTextInteraction;
	if(s->getProp("interaction/byMouse").toInt()==1)flags|=Qt::TextSelectableByMouse;
	if(s->getProp("interaction/byKeyboard").toInt()==1)flags|=Qt::TextSelectableByKeyboard;
	if(s->getProp("interaction/editable").toInt()==1)flags|=Qt::TextEditable;
	qDebug() << "flags: " << QString::number(flags);
	ui->textEdit->setTextInteractionFlags(flags);

	//COLORS

	QString sheet = "QTextEdit {"
		"background: "+s->getProp("color/background").toString()+";"
		"color: "+s->getProp("color/text").toString()+";"
		"}";
	qApp->setStyleSheet(sheet);

	//STATUSBAR

	customResize();
	updateStatus();
}

void MainWindow::submit(){
  QMessageBox::information(0,"Submit","OK");
}

void MainWindow::godmode(){
  QMessageBox::information(0,"Godmode","You have just entered god mode.");
}

void MainWindow::positionChanged(){
	updateStatus();
}

void MainWindow::updateStatus(){
	QString status="";
	if(s->getProp("statusbar/lineNumber").toInt())
		status += "Line number: " + QString::number(ui->textEdit->textCursor().blockNumber()) + " ";
	if(s->getProp("statusbar/columnNumber").toInt())
		status += "Column number: " + QString::number(ui->textEdit->textCursor().columnNumber()) + " ";
	if(s->getProp("statusbar/credits").toInt())
		status += "Number of credits: "+ QString::number(s->getProp("credits/count").toInt()) +" ";
	ui->label->setText(status);
}
