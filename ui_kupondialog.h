/********************************************************************************
** Form generated from reading UI file 'kupondialog.ui'
**
** Created: Mon Apr 19 21:35:18 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KUPONDIALOG_H
#define UI_KUPONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KuponDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *KuponDialog)
    {
        if (KuponDialog->objectName().isEmpty())
            KuponDialog->setObjectName(QString::fromUtf8("KuponDialog"));
        KuponDialog->setWindowModality(Qt::ApplicationModal);
        KuponDialog->resize(201, 85);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KuponDialog->sizePolicy().hasHeightForWidth());
        KuponDialog->setSizePolicy(sizePolicy);
        KuponDialog->setMinimumSize(QSize(201, 85));
        KuponDialog->setMaximumSize(QSize(201, 85));
        KuponDialog->setModal(true);
        buttonBox = new QDialogButtonBox(KuponDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 50, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalLayoutWidget = new QWidget(KuponDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 181, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        retranslateUi(KuponDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), KuponDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), KuponDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(KuponDialog);
    } // setupUi

    void retranslateUi(QDialog *KuponDialog)
    {
        KuponDialog->setWindowTitle(QApplication::translate("KuponDialog", "Vlo\305\276 kup\303\263n!", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("KuponDialog", "Cislo kuponu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KuponDialog: public Ui_KuponDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KUPONDIALOG_H
