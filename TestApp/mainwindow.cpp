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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sql;
}
