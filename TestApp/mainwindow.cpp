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

	/*QString str;
	QStringList list = sql->getLastTransactions(4);
	int i = 0;
	while (i < list.size()) {
		str += list.at(i) + "\n";
		++i;
	}
	ui->label->setText(str);*/

	sql->getLastTransactions(5);
	for (int i = 0; i < 5; ++i) {
		qDebug() << sql->getTransactionField(transaction_date,i);
		qDebug() << sql->getTransactionField(type,i);
		qDebug() << sql->getTransactionField(recipient,i);
		qDebug() << sql->getTransactionField(transaction_sum,i);
	}
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sql;
}
