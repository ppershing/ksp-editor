#ifndef KUPONDIALOG_H
#define KUPONDIALOG_H

#include <QDialog>
#include "settings.h"

namespace Ui {
    class KuponDialog;
}

class KuponDialog : public QDialog {
    Q_OBJECT
public:
	KuponDialog(Settings* settings, QWidget *parent = 0);
    ~KuponDialog();

public slots:
	void accept();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KuponDialog *ui;
	Settings* s;
};

#endif // KUPONDIALOG_H
