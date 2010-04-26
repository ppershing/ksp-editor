/********************************************************************************
** Form generated from reading UI file 'testdialog.ui'
**
** Created: Mon Apr 19 21:35:18 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTDIALOG_H
#define UI_TESTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>
#include "editor.h"

QT_BEGIN_NAMESPACE

class Ui_TestDialog
{
public:
    QTextBrowser *textBrowser;
    InputEditor *plainTextEdit;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButtonSubmit;
    QRadioButton *radioButtonCompileOnly;
    QRadioButton *radioButtonManualTest;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QLabel *label_2;

    void setupUi(QDialog *TestDialog)
    {
        if (TestDialog->objectName().isEmpty())
            TestDialog->setObjectName(QString::fromUtf8("TestDialog"));
        TestDialog->resize(396, 484);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TestDialog->sizePolicy().hasHeightForWidth());
        TestDialog->setSizePolicy(sizePolicy);
        TestDialog->setMinimumSize(QSize(396, 484));
        TestDialog->setMaximumSize(QSize(396, 484));
        TestDialog->setModal(true);
        textBrowser = new QTextBrowser(TestDialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(0, 30, 401, 461));
        textBrowser->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"font: 12pt \"MS Shell Dlg 2\";\n"
"color: rgb(255, 255, 255);"));
        plainTextEdit = new InputEditor(TestDialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 0, 0, 0));
        plainTextEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 12pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(0, 0, 0);"));
        horizontalLayoutWidget_2 = new QWidget(TestDialog);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 391, 25));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 0, 0, 0);
        radioButtonSubmit = new QRadioButton(horizontalLayoutWidget_2);
        radioButtonSubmit->setObjectName(QString::fromUtf8("radioButtonSubmit"));
        radioButtonSubmit->setChecked(true);

        horizontalLayout_2->addWidget(radioButtonSubmit);

        radioButtonCompileOnly = new QRadioButton(horizontalLayoutWidget_2);
        radioButtonCompileOnly->setObjectName(QString::fromUtf8("radioButtonCompileOnly"));
        radioButtonCompileOnly->setChecked(false);

        horizontalLayout_2->addWidget(radioButtonCompileOnly);

        radioButtonManualTest = new QRadioButton(horizontalLayoutWidget_2);
        radioButtonManualTest->setObjectName(QString::fromUtf8("radioButtonManualTest"));

        horizontalLayout_2->addWidget(radioButtonManualTest);

        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(horizontalLayoutWidget_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        pushButton = new QPushButton(horizontalLayoutWidget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(pushButton);

        label_2 = new QLabel(TestDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(310, 40, 0, 0));

        retranslateUi(TestDialog);

        QMetaObject::connectSlotsByName(TestDialog);
    } // setupUi

    void retranslateUi(QDialog *TestDialog)
    {
        TestDialog->setWindowTitle(QApplication::translate("TestDialog", "Submitni!", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("TestDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        radioButtonSubmit->setText(QApplication::translate("TestDialog", "Submit", 0, QApplication::UnicodeUTF8));
        radioButtonCompileOnly->setText(QApplication::translate("TestDialog", "Compile only", 0, QApplication::UnicodeUTF8));
        radioButtonManualTest->setText(QApplication::translate("TestDialog", "Manual test", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TestDialog", "jazyk:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("TestDialog", "cpp", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TestDialog", "pas", 0, QApplication::UnicodeUTF8)
        );
        pushButton->setText(QApplication::translate("TestDialog", "Do it!", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TestDialog", "Custom input:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
