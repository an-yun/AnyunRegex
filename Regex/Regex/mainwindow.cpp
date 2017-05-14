#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	regex_expression("(\\w)\\1{2,}")
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

