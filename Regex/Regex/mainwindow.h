#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <boost/regex.hpp>
#include <boost/timer/timer.hpp>
#include <QMainWindow>
#include <QDebug>
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


private:
    Ui::MainWindow *ui;
	boost::regex regex_expression;
	boost::match_results<std::string::const_iterator> what;
};

#endif // MAINWINDOW_H
