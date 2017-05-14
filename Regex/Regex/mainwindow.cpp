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


void MainWindow::on_search_button_clicked()
{
	QRegExp a("aa");
    std::string text = ui->search_text->text().toStdString();
	cpu_timer t;
    regex_search(text.cbegin(), text.cend(), what, regex_expression);
	t.stop();
    ui->result_label->setText(QString::fromStdString(what[0] + format(t.elapsed(),default_places," cost time %ws")));
}
