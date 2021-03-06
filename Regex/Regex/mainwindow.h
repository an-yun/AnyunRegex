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
	void regex_text_changed();
	void search_text_changed();
	void regex_text_cursor_position_changed();

private:
	static QColor red;
	static QColor black;
	static QColor white;
	static QColor match_color;
	static QString result_format;
	static QString result_header_format;
    Ui::MainWindow *ui;
	boost::wregex boost_regex;
	std::wregex std_regex;
	QRegExp q_regex;
	anyun_regex::NFA anyun_regex;

	QString regex_expression;
	QString search_text;
	int regex_select;
	bool error_flag;

	std::map<size_t,std::pair<size_t, std::vector<QString>>> search_result;

	void search();
	void show_search_result();
	void re_compile();
};

#endif // MAINWINDOW_H
