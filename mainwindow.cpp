#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	Logger::createInstance("log.txt");
	Logger::log("Starting application");
	ui->setupUi(this);
	s = new Settings();
	s->load();
	Logger::log("Settings loaded");
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
	connect(testDialog,SIGNAL(submitting()),this,SLOT(submitting()));
	connect(testDialog,SIGNAL(finished(int)),this,SLOT(submitFinished()));
	QShortcut* f7 = new QShortcut( Qt::Key_F7, this );
	connect(f7,SIGNAL(activated()),shopDialog,SLOT(show()));
	connect(shopDialog,SIGNAL(accepted()),this,SLOT(reload()));
	QShortcut* f8 = new QShortcut( Qt::Key_F8, this );
	connect(f8,SIGNAL(activated()),kuponDialog,SLOT(show()));
	connect(kuponDialog,SIGNAL(accepted()),this,SLOT(reload()));
	QShortcut* tazb = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_T,Qt::CTRL+Qt::Key_A,Qt::CTRL+Qt::Key_Z,Qt::CTRL+Qt::Key_B), this );
	connect(tazb,SIGNAL(activated()),this,SLOT(godmode()));

	connect(ui->textEdit,SIGNAL(keystroke()),this,SLOT(updateStatusBar()));

	idleTimer = new QTimer();
	idleTimer->setInterval(2000);
	connect(idleTimer, SIGNAL(timeout()), this, SLOT(checkIdle()));
	idleTimer->start();

	generalTimer = new QTimer();
	generalTimer->setInterval(1000);
	connect(generalTimer,SIGNAL(timeout()),this,SLOT(generalTimeout()));
	generalTimer->start();
	Logger::log("Application started");
}

MainWindow::~MainWindow()
{
    delete ui;
	delete shopDialog;
	delete kuponDialog;
	delete s;
	Logger::log("Ending application");
	Logger::destroyInstance();
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
	updateStatusBar();
}

void MainWindow::customResize(){
	s->decrement("credits/count",s->getInt("prices/resizeAction"));
	ui->textEdit->resize(this->width(),this->height()-(20*s->getInt("statusbar/enabled"))-(100*s->getInt("upgrades/showTaskDescription")));
	ui->textEdit->move(0,100*s->getInt("upgrades/showTaskDescription"));
	ui->textBrowser->resize(this->width(),100*s->getInt("upgrades/showTaskDescription"));
	ui->textBrowser->setHtml(testDialog->taskDescriptions.at(testDialog->currentTask));
	ui->statusBar->move(0,this->height()-(20*s->getInt("statusbar/enabled")));
}

void MainWindow::checkIdle(){
	if(ui->textEdit->lastEditTime.elapsed()>=10000 && !s->getBool("upgrades/screensaver")){
		QString text = ui->textEdit->document()->toPlainText();
		if(text.length()==0)return;
		int charToDelete = rand()%text.length();
		text.remove(charToDelete,1);
		ui->textEdit->document()->setPlainText(text);
	}
}

void MainWindow::generalTimeout(){
}

void MainWindow::show(){
	this->reload();
	QMainWindow::show();
}

void MainWindow::help(){
	QMessageBox::information(0,"Help","F1: Help\nF6: Submit\nF7: Kúp si upgrade\nF8: Použi kupón");
}

void MainWindow::reload(){
	s->load();
	ui->textEdit->s = s;
	testDialog->currentTask = s->getInt("tasks/done");

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
	if(s->getBool("upgrades/mouseInteraction"))flags|=Qt::TextSelectableByMouse;
	if(s->getBool("upgrades/keyboardInteraction"))flags|=Qt::TextSelectableByKeyboard;
	ui->textEdit->setTextInteractionFlags(flags);
	ui->textEdit->setUndoRedoEnabled(s->getBool("upgrades/undoRedo"));

	//COLORS

	QString sheet = "QTextEdit {"
		"background: "+s->getString("color/background")+";"
		"color: "+s->getString("color/text")+";"
		"}";
	qApp->setStyleSheet(sheet);

	//WINDOW

	bool vert = s->getBool("upgrades/resizeVertical");
	bool horiz = s->getBool("upgrades/resizeHorizontal");
	this->setMinimumSize(horiz?0:50,vert?0:50);
	this->setMaximumSize(horiz?999999:50,vert?999999:50);
	this->setSizePolicy(horiz?QSizePolicy::Preferred:QSizePolicy::Fixed,vert?QSizePolicy::Preferred:QSizePolicy::Fixed);
	customResize();
	updateStatusBar();
}

void MainWindow::submit(){
	idleTimer->stop();
	testDialog->program = ui->textEdit->toPlainText();
	testDialog->show();
}

void MainWindow::submitting(){
	if(!s->getBool("upgrades/saveOnSubmit"))
		clearText();
}

void MainWindow::submitFinished(){
	idleTimer->start();
	reload();
}

void MainWindow::godmode(){
	Logger::log("Godmode");
	QMessageBox::information(0,"Godmode","You have just entered god mode.");
	s->setProp("upgrades/readOnly",0);
	reload();
}

void MainWindow::clearText(){
	s->decrement("credits/count",s->getInt("prices/keyStroke"));
	updateStatusBar();
	if(s->getBool("upgrades/ctrln"))ui->textEdit->clear();
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
