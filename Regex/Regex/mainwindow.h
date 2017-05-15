#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <regex>
#include <boost/regex.hpp>
#include <boost/timer/timer.hpp>
#include <QMainWindow>
#include <QDebug>
#include <QRegExp>
#include "Matcher.h"

using boost::timer::cpu_timer;
using boost::timer::cpu_times;
using boost::timer::format;
using boost::timer::default_places;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void regex_selected_changed(int index);

private:
    Ui::MainWindow *ui;
	boost::basic_regex<char32_t> boost_regex;
	std::basic_regex<char32_t> std_regex;
	QRegExp q_regex;
	int regex_select;
};

#endif // MAINWINDOW_H
