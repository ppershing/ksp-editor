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

void KuponDialog::loadCodes(){
	QFile* f = new QFile("codes.txt");
	f->open(QIODevice::ReadOnly);
	while(!f->atEnd()){
		codes.insert(QString::fromAscii(f->readLine()).trimmed());
	}
	f->close();
}

void KuponDialog::clearCodes(){
	codes.clear();
}

int KuponDialog::kreditGain(QString code){
	return code.length()*code.length()*code.length();
}

void KuponDialog::accept(){
	QString code = ui->lineEdit->text();
	clearCodes();
	loadCodes();

	if(!codes.contains(code)){
		qDebug() << "wrong code";
		QDialog::reject();
		return;
	}
	if(s->isset("used/"+code)){
		qDebug() << "already used code";
		QDialog::reject();
		return;
	}

	s->setProp("used/"+code,1);
	s->increment("credits/count",kreditGain(code));
	QDialog::accept();
}
