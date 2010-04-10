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
	kuponDialog = new KuponDialog(s);
	testDialog = new TestDialog(s);
	QShortcut* ctrln = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_N), this );
	connect(ctrln,SIGNAL(activated()),this,SLOT(clearText()));
	QShortcut* f1 = new QShortcut( Qt::Key_F1, this );
	connect(f1,SIGNAL(activated()),this,SLOT(help()));
	QShortcut* f5 = new QShortcut( Qt::Key_F5, this );
	connect(f5,SIGNAL(activated()),this,SLOT(reload()));
	QShortcut* f6 = new QShortcut( Qt::Key_F6, this );
	connect(f6,SIGNAL(activated()),this,SLOT(submit()));
	QShortcut* f7 = new QShortcut( Qt::Key_F7, this );
	connect(f7,SIGNAL(activated()),shopDialog,SLOT(show()));
	connect(shopDialog,SIGNAL(accepted()),this,SLOT(reload()));
	QShortcut* f8 = new QShortcut( Qt::Key_F8, this );
	connect(f8,SIGNAL(activated()),kuponDialog,SLOT(show()));
	connect(kuponDialog,SIGNAL(accepted()),this,SLOT(reload()));
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
	ui->textEdit->resize(this->width(),this->height()-(20*s->getInt("statusbar/enabled"))-(100*s->getInt("upgrades/showTaskDescription")));
	ui->textEdit->move(0,100*s->getInt("upgrades/showTaskDescription"));
	ui->textBrowser->resize(this->width(),100*s->getInt("upgrades/showTaskDescription"));
	ui->statusBar->move(0,this->height()-(20*s->getInt("statusbar/enabled")));
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
	ui->textEdit->s = s;

	// FONT

	ui->textEdit->setFontFamily(s->getString("font/family"));
	QFont f = ui->textEdit->document()->defaultFont();
	f.setPointSize(s->getInt("font/size"));
	f.setWordSpacing(s->getInt("font/word_spacing"));
	f.setFamily(s->getString("font/family"));
	// tu sa doplnia dalsie nastavenia fontu
	ui->textEdit->document()->setDefaultFont(f);

	//INTERACTION

	QFlags<Qt::TextInteractionFlag> flags = Qt::NoTextInteraction;
	if(s->getBool("interaction/byMouse"))flags|=Qt::TextSelectableByMouse;
	if(s->getBool("interaction/byKeyboard"))flags|=Qt::TextSelectableByKeyboard;
	if(s->getBool("interaction/editable"))flags|=Qt::TextEditable;
	ui->textEdit->setTextInteractionFlags(flags);
	ui->textEdit->setUndoRedoEnabled(s->getBool("interaction/undoRedo"));

	//COLORS

	QString sheet = "QTextEdit {"
		"background: "+s->getString("color/background")+";"
		"color: "+s->getString("color/text")+";"
		"}";
	qApp->setStyleSheet(sheet);

	//STATUSBAR

	customResize();
	updateStatusBar();
}

void MainWindow::submit(){
	testDialog->program = ui->textEdit->toPlainText();
	testDialog->show();
}

void MainWindow::godmode(){
	QMessageBox::information(0,"Godmode","You have just entered god mode.");
	s->setProp("interaction/editable",1);
	reload();
}

void MainWindow::positionChanged(){
	updateStatusBar();
}

void MainWindow::clearText(){
	ui->textEdit->clear();
}

void MainWindow::updateStatusBar(){
	QString status="";
	if(s->getBool("statusbar/lineNumber"))
		status += "Line number: " + QString::number(ui->textEdit->textCursor().blockNumber()) + " ";
	if(s->getBool("statusbar/columnNumber"))
		status += "Column number: " + QString::number(ui->textEdit->textCursor().columnNumber()) + " ";
	if(s->getBool("statusbar/credits"))
		status += "Number of credits: " + QString::number(s->getInt("credits/count")) + " ";
	ui->label->setText(status);
}
