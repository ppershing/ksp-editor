#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	s = new Settings();
	QShortcut* shortcut = new QShortcut( Qt::Key_F5, this );
	connect(shortcut,SIGNAL(activated()),this,SLOT(reload()));
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::show(){
	this->reload();
	QMainWindow::show();
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
}

void MainWindow::on_pushButton_clicked()
{
	this->reload();
}
