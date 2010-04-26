#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("KSP");
	QCoreApplication::setOrganizationDomain("ksp.sk");
	QCoreApplication::setApplicationName("Tazba");

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
