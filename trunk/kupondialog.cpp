#include "kupondialog.h"
#include "ui_kupondialog.h"

KuponDialog::KuponDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KuponDialog)
{
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
