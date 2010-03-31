#include "kupondialog.h"
#include "ui_kupondialog.h"

KuponDialog::KuponDialog(Settings* settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KuponDialog)
{
	s = settings;
    ui->setupUi(this);
}

KuponDialog::~KuponDialog()
{
    delete ui;
}

void KuponDialog::changeEvent(QEvent *e)
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

void KuponDialog::accept(){
	if(ui->lineEdit->text()=="tazb")
		s->increment("credits/count",1);
	QDialog::accept();
}
