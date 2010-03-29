#ifndef KUPONDIALOG_H
#define KUPONDIALOG_H

#include <QDialog>

namespace Ui {
    class KuponDialog;
}

class KuponDialog : public QDialog {
    Q_OBJECT
public:
    KuponDialog(QWidget *parent = 0);
    ~KuponDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KuponDialog *ui;
};

#endif // KUPONDIALOG_H
