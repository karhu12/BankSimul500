#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	sql(new DLLMySql),
	serviceFee(new ServiceFee),
	serial(new DLLSerialPort),
	pin(new DLLPinCode)
{
	ui->setupUi(this);
	connect(serviceFee, SIGNAL(passServiceFee(unsigned int,double)), this, SLOT(handle(unsigned int,double)));
	connect(serial, SIGNAL(passID(QString)), this, SLOT(handleSerial(QString)));
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

void MainWindow::on_pushButton_3_clicked()
{
	int payment = sql->chargePayment(100);
	if (payment == 0) {
		last = sql->getLastTransactions();
		sql->createTransactionStrings(s,t,r,x,start,end);
		ui->label->setText(s);
		ui->label_2->setText(t);
		ui->label_3->setText(r);
		ui->label_4->setText(x);
	}
	else if (payment == 1) {
		qDebug() << "Virhe maksu liian suuri";
	}
	else {
		qDebug() << "Maksussa tapahtui virhe...";
	}
}

void MainWindow::on_pushButton_4_clicked()
{
	if (sql->lockCurrentCard()) {
		qDebug() << "Deactivated card...";
		serviceFee->stopServiceFee();
		sql->disconnect();
		connect(serial, SIGNAL(passID(QString)), this, SLOT(handleSerial(QString)));
		ui->label->setText("");
		ui->label_2->setText("");
		ui->label_3->setText("");
		ui->label_4->setText("");
	}
	else {
		qDebug() << "Failure deactivating card...";
	}
}

void MainWindow::handle(unsigned int duration, double fee) {
	totalServiceFee = fee;
	totalServiceTime = duration;
	if (serviceFee->isFeeOverBalance(sql->getAccountInformation(balance).toDouble())) {
		if (sql->chargePayment(fee) == 1) {
			sql->chargePayment(sql->getAccountInformation(balance).toFloat());
		}
		close();
	}
	ui->label_5->setText(QString::number(duration));
	ui->label_6->setText(QString::number(fee));
}

void MainWindow::handleSerial(QString cardNumber) {
	if (sql->setup()) {
		if (sql->findAccountWithCardNumber(cardNumber)) {
			if (!sql->isCardLocked()) {
				pin->interfaceFunction();
				if (sql->confirmAccountPin(pin->interfaceFunctionReturnFunction())) {
					serviceFee->startServiceFee();
					last = sql->getLastTransactions();
					start = 0; end = 10;
					sql->createTransactionStrings(s,t,r,x,0);
					ui->label->setText(s);
					ui->label_2->setText(t);
					ui->label_3->setText(r);
					ui->label_4->setText(x);
					serial->disconnect();
				}
				else {
					qDebug() << "Account pin code incorrect";
					sql->disconnect();
				}
			}
			else {
				qDebug() << "Card is locked...";
				sql->disconnect();
			}
		}
		else {
			qDebug() << "Account not found...";
			sql->disconnect();
		}
	}
	else {
		qDebug() << "Setup failed... ";
	}
}

void MainWindow::on_pushButton_5_clicked()
{
	if (serviceFee->isOverFeeLevel()) {
		sql->chargePayment(totalServiceFee);
		qDebug() << "Lose: " << totalServiceFee << "Cash";
	}
	else {
		sql->receivePayment(totalServiceFee);
		qDebug() << "Gain: " << totalServiceFee << "Cash";
	}
	serviceFee->stopServiceFee();
	sql->disconnect();
	connect(serial, SIGNAL(passID(QString)), this, SLOT(handleSerial(QString)));
	ui->label->setText("");
	ui->label_2->setText("");
	ui->label_3->setText("");
	ui->label_4->setText("");
}
