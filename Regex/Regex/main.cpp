#include <iostream>
#include <string>
#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#include "Matcher.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
	a.setWindowIcon(QIcon("icon.png"));
    return a.exec();
}
