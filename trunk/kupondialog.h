#ifndef KUPONDIALOG_H
#define KUPONDIALOG_H

#include <QDialog>
#include <QFile>
#include <QSet>
#include <QDebug>
#include "settings.h"

namespace Ui {
    class KuponDialog;
}

class KuponDialog : public QDialog {
    Q_OBJECT
public:
	KuponDialog(Settings* settings, QWidget *parent = 0);
    ~KuponDialog();
	void loadCodes();
	void clearCodes();
	int kreditGain(QString code);

public slots:
	void accept();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KuponDialog *ui;
	Settings* s;
	QSet<QString> codes;
};

#endif // KUPONDIALOG_H
