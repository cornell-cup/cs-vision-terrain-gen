#include "mainwindow.h"
#include <QtGui>
#include <QPushButton>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


//    QPushButton *button = new QPushButton(
//        QApplication::translate("childwidget", "Press me"), &w);
//    button->move(150, 100);
//    button->show();

    return a.exec();
}


