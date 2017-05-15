#include  <exception>
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

void MainWindow::regex_selected_changed(int index)
{
	qDebug() << "select regex :" << index;
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
	std::wstring w_search_text = search_text.toStdWString();
	try
	{
		switch (regex_select)
		{
		case 0:
			{
				boost_regex.set_expression(w_regex_expression);
				boost::wsregex_iterator b(w_search_text.begin(), w_search_text.end(), boost_regex);
				boost::wsregex_iterator e;
				for (;b!=e;b++)
					ui->search_result_textEdit->append(QString::fromStdWString((*b).str()));
				break;
			}

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
	search_text = ui->search_textEdit->toPlainText();
	qDebug() << search_text;
}
