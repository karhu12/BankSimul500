#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dllmysql.h"
#include "servicefee.h"
#include "dllserialport.h"
#include "dllpincode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
	finishProgram();

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void handle(unsigned int duration, double fee);
	void on_pushButton_5_clicked();
	void handleSerial(QString cardNumber);

private:
    Ui::MainWindow *ui;
    DLLMySql *sql;
	DLLMySql *sql2;
	ServiceFee *serviceFee;
	DLLSerialPort *serial;
	DLLPinCode *pin;
	int start, end;
	int last;
	double totalServiceFee;
	unsigned totalServiceTime;
	QString s,t,r,x;
};

#endif // MAINWINDOW_H
