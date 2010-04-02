#include <QDebug>
#include "shopdialog.h"
#include "ui_shopdialog.h"

ShopDialog::ShopDialog(Settings* settings,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShopDialog)
{
    ui->setupUi(this);
	s = settings;
	checkBoxes["fontSize1"]=ui->checkBoxFontSize1;
	checkBoxes["fontSize2"]=ui->checkBoxFontSize2;
	checkBoxes["fontSize3"]=ui->checkBoxFontSize3;
	checkBoxes["wordSpacing"]=ui->checkBoxWordSpacing;
	checkBoxes["fontFamily1"]=ui->checkBoxFontFamily1;
	checkBoxes["fontFamily2"]=ui->checkBoxFontFamily2;
	checkBoxes["contrast1"]=ui->checkBoxContrast1;
	checkBoxes["contrast2"]=ui->checkBoxContrast2;
	checkBoxes["contrast3"]=ui->checkBoxContrast3;
	checkBoxes["keyboardInteraction"]=ui->checkBoxKeyboardNavigation;
	checkBoxes["statusBar"]=ui->checkBoxStatusBar;
	checkBoxes["lineNumber"]=ui->checkBoxLineNumber;
	checkBoxes["columnNumber"]=ui->checkBoxColumnNumber;
	checkBoxes["credits"]=ui->checkBoxCredits;

	QMapIterator<QString, QCheckBox*> i(checkBoxes);
	while(i.hasNext()){
		i.next();
		connect(i.value(),SIGNAL(clicked()),this,SLOT(reload()));
	}
	prices["fontSize1"]=1;
	prices["fontSize2"]=1;
	prices["fontSize3"]=1;
	prices["wordSpacing"]=1;
	prices["fontFamily1"]=1;
	prices["fontFamily2"]=1;
	prices["contrast1"]=1;
	prices["contrast2"]=1;
	prices["contrast3"]=1;
	prices["keyboardInteraction"]=1;
	prices["statusBar"]=1;
	prices["lineNumber"]=1;
	prices["columnNumber"]=1;
	prices["credits"]=1;
}

ShopDialog::~ShopDialog()
{
    delete ui;
}

void ShopDialog::changeEvent(QEvent *e)
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

void ShopDialog::show(){
	reset();
	checkAvailability();
	QDialog::show();
}

void ShopDialog::reload(){
	QString propClicked = "";
	if(this->sender()){
		propClicked = this->checkBoxToPropName((QCheckBox*)this->sender());
	}
	if(checkBoxes[propClicked]->isChecked())
		credits -= prices[propClicked];
	else
		credits += prices[propClicked];
	checkAvailability();
}

void ShopDialog::accept(){
	QDialog::accept();
}

void ShopDialog::checkAvailability(){
	/*
podla tabulky:
zaskrtnute mamNaTo mamTo-------DIS
zaskrtnute mamNaTo nemamTo-----OK
zaskrtnute nemamNaTo mamTo-----DIS
zaskrtnute nemamNaTo nemamTo---OK
nezaskrtnute mamNaTo mamTo-----WTF
nezaskrtnute mamNaTo nemamTo---OK
nezaskrtnute nemamNaTo mamTo---WTF
nezaskrtnute nemamNaTo nemamTo-DIS
	*/
	QMapIterator<QString, QCheckBox*> i(checkBoxes);
	while(i.hasNext()){
		i.next();
		if(i.value()->isChecked() && credits>=prices[i.key()] && s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(false);
		if(i.value()->isChecked() && credits>=prices[i.key()] && !s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(true);
		if(i.value()->isChecked() && credits<prices[i.key()] && s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(false);
		if(i.value()->isChecked() && credits<prices[i.key()] && !s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(true);

		if(!i.value()->isChecked() && credits>=prices[i.key()] && !s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(true);
		if(!i.value()->isChecked() && credits<prices[i.key()] && !s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(false);
	}
}

void ShopDialog::reset(){
	credits = s->getInt("credits/count");
	QMapIterator<QString, QCheckBox*> i(checkBoxes);
	while(i.hasNext()){
		i.next();
		i.value()->setChecked(s->getBool("upgrades/"+i.key()));
	}
}

QString ShopDialog::checkBoxToPropName(QCheckBox *checkBox){
	return checkBoxes.key(checkBox,"");
}
