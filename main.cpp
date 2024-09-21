#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.move(1000, 100);                                                                                                                              //спавн окна по координатам

    QPalette backgrownd;
    backgrownd.setBrush(QPalette::Active, QPalette::Base, QBrush(QPixmap("C:/Users/Di/Documents/shooter/resources/sprites/myspace.png")));          //сюда для космоса
    backgrownd.setBrush(QPalette::Active, QPalette::Window, QColor(40, 40, 40));                                                                    //сюда для рамки

    w.setPalette(backgrownd);
    w.setAutoFillBackground(true);

    w.show();
    return a.exec();
}
