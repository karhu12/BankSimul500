#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	serviceFee(new ServiceFee)
{
	ui->setupUi(this);
	connect(serviceFee, SIGNAL(passServiceFee(unsigned int,double)), SLOT(serviceFeeHandle(unsigned int,double)));
	ui->pushButton->hide();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::serviceFeeHandle(unsigned int duration, double fee) {
	ui->label->setText(QString::number(duration));
	if (fee <= 0) {
		ui->label_2->setStyleSheet("QLabel { color: green }");
	}
	else {
		ui->label_2->setStyleSheet("QLabel { color: red }");
	}
	ui->label_2->setText(QString::number(fee));
}

void MainWindow::on_pushButton_clicked()
{
	serviceFee->stopServiceFee();
	ui->pushButton->hide();
	ui->pushButton_2->show();
}

void MainWindow::on_pushButton_2_clicked()
{
	serviceFee->startServiceFee();
	ui->pushButton->show();
	ui->pushButton_2->hide();
}
