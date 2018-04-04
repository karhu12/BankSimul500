#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sql(new DLLMySql)
{
	ui->setupUi(this);
	if (!sql->setup()) {
		qDebug() << "Setup failed... exit with failure";
		this->close();
	}

	qDebug() << ((sql->findAccountWithCardNumber("0A0079E538"))
		? "Account found with card number" : "Account not found with card number...");

	qDebug() << ((sql->confirmAccountPin("1234")) ? "valid pin" : "Invalid pin");
	last = sql->getLastTransactions();
	start = 0; end = 9;
	sql->createTransactionStrings(s,t,r,x,start,end);
	ui->label->setText(s);
	ui->label_2->setText(t);
	ui->label_3->setText(r);
	ui->label_4->setText(x);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sql;
}

void MainWindow::on_pushButton_clicked()
{
	if (start + 10 < last) {
		start += 10; end += 10;
		sql->createTransactionStrings(s,t,r,x,start,end);
		ui->label->setText(s);
		ui->label_2->setText(t);
		ui->label_3->setText(r);
		ui->label_4->setText(x);
	}
}

void MainWindow::on_pushButton_2_clicked()
{
	if (start - 10 >= 0) {
		start -= 10; end -= 10;
		sql->createTransactionStrings(s,t,r,x,start,end);
		ui->label->setText(s);
		ui->label_2->setText(t);
		ui->label_3->setText(r);
		ui->label_4->setText(x);
	}
}
