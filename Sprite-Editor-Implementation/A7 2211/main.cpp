#include "mainwindow.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model m;
    sizeDialog sd;
    MainWindow w(&m,&sd);
    w.show();
    return a.exec();
}
