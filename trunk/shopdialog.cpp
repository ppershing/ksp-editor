#include "shopdialog.h"
#include "ui_shopdialog.h"

ShopDialog::ShopDialog(Settings* settings,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShopDialog)
{
    ui->setupUi(this);
	s = settings;
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

void ShopDialog::accept(){
	QDialog::accept();
}
