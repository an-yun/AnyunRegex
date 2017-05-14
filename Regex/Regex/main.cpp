#include <iostream>
#include <string>
#include "mainwindow.h"
#include <QApplication>
#include "Matcher.h"
#include <boost/regex.hpp>


int main(int argc, char *argv[])
{
	boost::regex regex_expression("(\\w)\\1{2,}");
	boost::match_results<std::string::const_iterator> what;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
