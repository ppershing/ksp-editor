#ifndef SHOPDIALOG_H
#define SHOPDIALOG_H

#include <QDialog>
#include "settings.h"

namespace Ui {
    class ShopDialog;
}

class ShopDialog : public QDialog {
    Q_OBJECT
public:
	ShopDialog(Settings* settings,QWidget *parent = 0);
    ~ShopDialog();

public slots:
	void accept();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ShopDialog *ui;
	Settings* s;
};

#endif // SHOPDIALOG_H
