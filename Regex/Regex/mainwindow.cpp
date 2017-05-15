#include  <exception>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::regex_selected_changed(int index)
{
	qDebug() << "select regex :" << index;
	QString regex_expression = ui->regex_textEdit->toPlainText();
	regex_select = index;
	try
	{
		switch (regex_select)
		{
		case 0:
			boost_regex.set_expression(regex_expression.toStdU32String());
			break;
		}
	}
	catch(std::exception e)
	{
		
	}
    
}
