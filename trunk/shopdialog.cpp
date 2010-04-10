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
	checkBoxes["mouseInteraction"]=ui->checkBoxMouseNavigation;
	checkBoxes["statusBar"]=ui->checkBoxStatusBar;
	checkBoxes["lineNumber"]=ui->checkBoxLineNumber;
	checkBoxes["columnNumber"]=ui->checkBoxColumnNumber;
	checkBoxes["credits"]=ui->checkBoxCredits;
	checkBoxes["paste"]=ui->checkBoxPaste;
	checkBoxes["undoRedo"]=ui->checkBoxUndoRedo;
	checkBoxes["backspace"]=ui->checkBoxBackspace;
	checkBoxes["showPrices"]=ui->checkBoxShowPrices;
	checkBoxes["cheaperKeystrokes1"]=ui->checkBoxCheaperKeystrokes1;
	checkBoxes["cheaperKeystrokes2"]=ui->checkBoxCheaperKeystrokes2;
	checkBoxes["readOnly"]=ui->checkBoxReadOnly;
	checkBoxes["saveOnSubmit"]=ui->checkBoxSaveOnSubmit;
	checkBoxes["showCompilationStatus"]=ui->checkBoxShowCompilationStatus;
	checkBoxes["showCompilationWarnings"]=ui->checkBoxShowCompilationWarnings;
	checkBoxes["compileOnly"]=ui->checkBoxCompileOnly;
	checkBoxes["manualTest"]=ui->checkBoxManualTest;

	QMapIterator<QString, QCheckBox*> i(checkBoxes);
	while(i.hasNext()){
		i.next();
		connect(i.value(),SIGNAL(toggled(bool)),this,SLOT(reload()));
	}

	reqs["lineNumber"] << "statusBar";
	reqs["columnNumber"] << "statusBar";
	reqs["credits"] << "statusBar";
	reqs["fontSize2"] << "fontSize1";
	reqs["fontSize3"] << "fontSize1" << "fontSize2";
	reqs["fontFamily2"] << "fontFamily1";
	reqs["contrast2"] << "contrast1";
	reqs["contrast3"] << "contrast1" << "contrast2";
	reqs["cheaperKeystrokes2"] << "cheaperKeystrokes1";
	reqs["showCompilationWarnings"] << "showCompilationStatus";
	reqs["compileOnly"] << "showCompilationStatus";
	reqs["manualTest"] << "compileOnly";

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
		credits -= s->getInt("prices/"+propClicked);
	else
		credits += s->getInt("prices/"+propClicked);
	// credits sa upravuje len lokalne, aby sa upravilo availability, realne sa znizia credits az vo fcii accept
	checkAvailability();
}

void ShopDialog::accept(){
	QMapIterator<QString, QCheckBox*> i(checkBoxes);
	while(i.hasNext()){
		i.next();
		if(i.value()->isChecked() && !s->getBool("upgrades/"+i.key())){
			upgrade(i.key());
		}
	}
	s->setProp("credits/count",credits);
	QDialog::accept();
}

void ShopDialog::checkAvailability(){
	/*
podla tabulky:
zaskrtnute mamNaTo mamTo-------DIS
zaskrtnute mamNaTo nemamTo-----OK (ale len ak to nie je req pre iny checknuty checkbox)
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
		bool mamNaTo = bool(credits>=s->getInt("prices/"+i.key()));
		if(reqs.value(i.key()).count()>0){
			foreach(QString req,reqs.value(i.key())){
				mamNaTo &= (checkBoxes[req]->isChecked());
			}
		}
		if(i.value()->isChecked() && mamNaTo && s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(false);
		if(i.value()->isChecked() && !s->getBool("upgrades/"+i.key())){
			i.value()->setEnabled(true);
			QMapIterator<QString, QStringList> j(reqs);
			while(j.hasNext()){
				j.next();
				if(j.value().contains(i.key()) && checkBoxes[j.key()]->isChecked())
					i.value()->setEnabled(false);
			}
		}
		if(i.value()->isChecked() && !mamNaTo && s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(false);
		if(!i.value()->isChecked() && mamNaTo && !s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(true);
		if(!i.value()->isChecked() && !mamNaTo && !s->getBool("upgrades/"+i.key()))
			i.value()->setEnabled(false);
	}
}

void ShopDialog::reset(){
	QMapIterator<QString, QCheckBox*> i(checkBoxes);
	while(i.hasNext()){
		i.next();
		i.value()->setChecked(s->getBool("upgrades/"+i.key()));
	}
	credits = s->getInt("credits/count");
}

void ShopDialog::upgrade(QString propName){
	s->setProp("upgrades/"+propName,1);
	if(propName=="fontSize1")s->setProp("font/size",40);
	if(propName=="fontSize2")s->setProp("font/size",20);
	if(propName=="fontSize3")s->setProp("font/size",10);
	if(propName=="wordSpacing")s->setProp("font/word_spacing",0);
	if(propName=="fontFamily1")s->setProp("font/family","Arial");
	if(propName=="fontFamily2")s->setProp("font/family","Courier");
	if(propName=="contrast1")s->setProp("color/text","#333333");
	if(propName=="contrast2")s->setProp("color/text","#666666");
	if(propName=="contrast3")s->setProp("color/text","#ffffff");
	if(propName=="keyboardInteraction")s->setProp("interaction/byKeyboard",1);
	if(propName=="mouseInteraction")s->setProp("interaction/byMouse",1);
	if(propName=="statusBar")s->setProp("statusbar/enabled",1);
	if(propName=="lineNumber")s->setProp("statusbar/lineNumber",1);
	if(propName=="columnNumber")s->setProp("statusbar/columnNumber",1);
	if(propName=="credits")s->setProp("statusbar/credits",1);
	if(propName=="paste")s->setProp("interaction/canPaste",1);
	if(propName=="undoRedo")s->setProp("interaction/undoRedo",1);
	if(propName=="backspace")s->setProp("interaction/backspace",1);
	if(propName=="showPrices"){
		s->setProp("shopping/showPrices",1);
		QMapIterator<QString, QCheckBox*> i(checkBoxes);
		while(i.hasNext()){
			i.next();
			i.value()->setText(i.value()->text() + " (" + QString::number(s->getInt("prices/"+i.key())) + ")");
		}
	}
	if(propName=="cheaperKeystrokes1")s->setProp("prices/keyStroke",1);
	if(propName=="cheaperKeystrokes2")s->setProp("prices/keyStroke",0);
	if(propName=="readOnly")s->setProp("interaction/editable",0);

}

QString ShopDialog::checkBoxToPropName(QCheckBox *checkBox){
	return checkBoxes.key(checkBox,"");
}
