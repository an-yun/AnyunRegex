#include <exception>
#include <algorithm>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextBlock>
#include "DirectedGraph.h"


QColor MainWindow::red(255, 0, 0);
QColor MainWindow::black(0, 0, 0);
QColor MainWindow::white(255, 255, 255);
QColor MainWindow::match_color(103, 204, 255);
QString MainWindow::result_format("Group %1:	%2");
QString MainWindow::result_header_format("mathch postion %1-%2");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	regex_select(0),
	error_flag(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::regex_selected_changed(int index)
{
	qDebug() << "select regex :" << index;
	if(regex_select == index) return;
	regex_select = index;
	re_compile();
}

void MainWindow::regex_text_changed()
{
	qDebug() << "regex text changed";
	QString temp_regex = ui->regex_textEdit->toPlainText();
	if(temp_regex == regex_expression) return;
	regex_expression = temp_regex;
	re_compile();
}

void MainWindow::search_text_changed()
{
	QString temp_text = ui->search_textEdit->toPlainText();;
	if (search_text == temp_text) return;
	search_text = temp_text;
	qDebug() <<"search text :"<< search_text;
	search();
	show_search_result();
}

void MainWindow::regex_text_cursor_position_changed()
{
	size_t position = ui->search_textEdit->textCursor().position();
	auto find_result = search_result.upper_bound(position);
	if (find_result == search_result.begin()) return;
	auto &one_match = *(--find_result);
	if (position > one_match.second.first) return;
	auto &groups = one_match.second.second;
	auto &search_result_textEdit = ui->search_result_textEdit;
	search_result_textEdit->clear();
	size_t group_size = groups.size();
	search_result_textEdit->append(result_header_format.arg(one_match.first).arg(one_match.second.first));
	for (size_t i = 0; i < group_size; i++)
		search_result_textEdit->append(result_format.arg(i,3).arg(groups[i]));
}

void MainWindow::search()
{
	search_result.clear();
	if(error_flag || search_text.length() == 0|| regex_expression.length() == 0)return;
	std::wstring ws_search_text = search_text.toStdWString();
	std::string s_search_text = search_text.toStdString();
	cpu_timer t;
	switch (regex_select)
	{
		case 0:
		{
			boost::wsregex_iterator b(ws_search_text.begin(), ws_search_text.end(), boost_regex);
			boost::wsregex_iterator e;
			for (; b != e; b++)
			{
				auto &one_search_result = *b;
				std::vector<QString> groups;
				size_t groups_amount= one_search_result.size();
				for (size_t i=0;i< groups_amount;i++)
					groups.push_back(QString::fromStdWString(one_search_result.str(i)));
				size_t match_start_positoin = std::distance(ws_search_text.cbegin(),one_search_result[0].first);
				size_t match_end_position = match_start_positoin +one_search_result.length(0);
				qDebug() << "start " << match_start_positoin << " end " << match_end_position;
				search_result[match_start_positoin] = { match_end_position,groups };
			}
			break;
		}
		case 1:
		{
			std::wsregex_iterator b(ws_search_text.begin(), ws_search_text.end(), std_regex);
			std::wsregex_iterator e;
			for (; b != e; b++)
			{
				auto &one_search_result = *b;
				std::vector<QString> groups;
				size_t groups_amount = one_search_result.size();
				for (size_t i = 0; i< groups_amount; i++)
					groups.push_back(QString::fromStdWString(one_search_result.str(i)));
				size_t match_start_positoin = std::distance(ws_search_text.cbegin(), one_search_result[0].first);
				size_t match_end_position = match_start_positoin + one_search_result.length(0);
				qDebug() << "start " << match_start_positoin << " end " << match_end_position;
				search_result[match_start_positoin] = { match_end_position,groups };
			}
			break;
		}
		case 2:
		{
			int position = 0;
			while ((position = q_regex.indexIn(search_text,position))!= -1)
			{
				std::vector<QString> groups;
				size_t groups_amount = q_regex.captureCount();
				for (size_t i = 0; i<= groups_amount; i++)
					groups.push_back(q_regex.cap(i));
				size_t match_end_position = position + q_regex.matchedLength();
				qDebug() << "start " << position << " end " << match_end_position;
				search_result[position] = { match_end_position,groups };
				position = match_end_position;
			}
			break;
		}
		case 3:
		{
			::anyun_regex::NFAMatcher anyun_search_result;
			anyun_search_result.set_content(s_search_text, anyun_regex);
			while(anyun_search_result.search())
			{
				std::vector<QString> groups;
				size_t groups_amount = anyun_search_result.group_count();
				for (size_t i = 0; i < groups_amount; i++)
					groups.push_back(QString::fromStdString(anyun_search_result.group(i)));
				//here need some code to transform string position to wstring position
				size_t start = anyun_search_result.start();
				size_t end = anyun_search_result.end();
				qDebug() << "start " << start << " end " << end;
				search_result[start] = { end,groups };
			}
			break;
		}
		default:
			break;
	}
	t.stop();
	ui->time_label->setText(QString::fromStdString(format(t.elapsed(), default_places, "用时: %ws")));
}

void MainWindow::show_search_result()
{
	QTextCursor cursor = ui->search_textEdit->textCursor();
	int current_position = cursor.position();
	ui->search_textEdit->selectAll();
	ui->search_textEdit->setTextBackgroundColor(white);
	ui->regex_textEdit->textCursor().clearSelection();
	for(auto m_start = search_result.begin(),m_end = search_result.end();m_start!=m_end;m_start++)
	{
		auto &one_positon = *m_start;
		cursor.setPosition(one_positon.first);
		cursor.setPosition(one_positon.second.first,QTextCursor::KeepAnchor);
		ui->search_textEdit->setTextCursor(cursor);
		ui->search_textEdit->setTextBackgroundColor(match_color);
	}
	cursor.setPosition(current_position);
	ui->search_textEdit->setTextCursor(cursor);
	ui->search_textEdit->setTextBackgroundColor(white);
}

void MainWindow::re_compile()
{
	std::wstring w_regex_expression = regex_expression.toStdWString();
	try
	{
		switch (regex_select)
		{
		case 0:
			boost_regex.set_expression(w_regex_expression);
			break;
		case 1:
			std_regex.assign(w_regex_expression);
			break;
		case 2:
			q_regex.setPattern(regex_expression);
			if (!q_regex.isValid()) throw std::exception(q_regex.errorString().toStdString().c_str());
			break;
		case 3:
			anyun_regex.compile(regex_expression.toStdString());
			if (anyun_regex.get_compile_result_code() != ::anyun_regex::RegexParseCode::REGEX_PARSE_OK)
				throw std::exception(anyun_regex.get_compile_message());
			break;
		default:

			break;
		}
		error_flag = false;
		QTextCursor cursor = ui->regex_textEdit->textCursor();
		ui->regex_tip_label->clear();
		ui->regex_textEdit->selectAll();
		ui->regex_textEdit->setTextColor(black);
		ui->regex_textEdit->setTextCursor(cursor);
		search();
		show_search_result();
	}
	catch (std::exception e)
	{
		error_flag = true;
		ui->regex_tip_label->setText(QStringLiteral("<font color=red>regex error: %1</font>").arg(e.what()));
		QTextCursor cursor = ui->regex_textEdit->textCursor();
		ui->regex_textEdit->selectAll();
		ui->regex_textEdit->setTextColor(red);
		ui->regex_textEdit->setTextCursor(cursor);
		ui->regex_textEdit->setTextColor(black);
	}
}
