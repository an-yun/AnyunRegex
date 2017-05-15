#include <exception>
#include <algorithm>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "DirectedGraph.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	regex_select(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QColor MainWindow::red(255, 0, 0);
QColor MainWindow::black(0, 0, 0);
QColor MainWindow::white(255, 255, 255);
QColor MainWindow::match_color(103, 204, 255);

void MainWindow::regex_selected_changed(int index)
{
	qDebug() << "select regex :" << index;
	if(regex_select == index) return;
	regex_select = index;
	regex_text_changed();
}

void MainWindow::regex_text_changed()
{
	qDebug() << "regex text changed";
	QString temp_regex = ui->regex_textEdit->toPlainText();
	if(temp_regex == regex_expression) return;
	else regex_expression = temp_regex;
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
			break;
		case 3:
			anyun_regex.compile(regex_expression.toStdString());
			if (anyun_regex.get_compile_result_code() != ::anyun_regex::RegexParseCode::REGEX_PARSE_OK)
				throw std::exception(anyun_regex.get_compile_message());
			break;
		default:
			break;
		}
		search();
		show_search_result();
	}
	catch (std::exception e)
	{
		QMessageBox::information(this, QStringLiteral("正则表达式非法"), e.what());
		ui->regex_textEdit->selectAll();
		ui->regex_textEdit->setTextColor(red);
		ui->regex_textEdit->textCursor().clearSelection();
		ui->regex_textEdit->setTextColor(black);
	}
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

void MainWindow::search()
{
	search_result.clear();
	match_positions.clear();
	std::wstring w_search_text = search_text.toStdWString();
	switch (regex_select)
	{
		case 0:
		{
			boost::wsregex_iterator b(w_search_text.begin(), w_search_text.end(), boost_regex);
			boost::wsregex_iterator e;
			for (; b != e; b++)
			{
				auto &one_search_result = *b;
				std::vector<QString> groups;
				size_t groups_amount= one_search_result.size();
				for (size_t i=0;i< groups_amount;i++)
					groups.push_back(QString::fromStdWString(one_search_result.str(i)));
				search_result.push_back(groups);
				size_t match_start_positoin = std::distance(w_search_text.cbegin(),one_search_result[0].first);
				size_t match_length = one_search_result.length(0);
				qDebug() << "start " << match_start_positoin << " length " << match_length;
				match_positions.push_back({ match_start_positoin,match_length });
			}
			break;
		}

		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}

void MainWindow::show_search_result()
{
	QTextCursor cursor = ui->search_textEdit->textCursor();
	int current_position = cursor.position();
	ui->search_textEdit->selectAll();
	ui->search_textEdit->setTextBackgroundColor(white);
	ui->regex_textEdit->textCursor().clearSelection();
	for(std::pair<size_t,size_t> &one_positon:match_positions)
	{
		
		cursor.setPosition(one_positon.first);
		cursor.setPosition(one_positon.first+one_positon.second,QTextCursor::KeepAnchor);
		ui->search_textEdit->setTextCursor(cursor);
		ui->search_textEdit->setTextBackgroundColor(match_color);
	}
	cursor.setPosition(current_position);
	ui->search_textEdit->setTextCursor(cursor);
	ui->search_textEdit->setTextBackgroundColor(white);
}
