#include "dllserialport_engine.h"

DLLSerialPort_engine::DLLSerialPort_engine()
{
    serial = new QSerialPort(this);
	serial->setPortName("COM11");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::HardwareControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadOnly);
    QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(handleSignal()));
}

void DLLSerialPort_engine::handleSignal() {
    QString cardID = serial->readAll();
    cardID = cardID.simplified();
    cardID.replace("-","");
    cardID.replace(">","");
    cardID.replace(" ","");
    emit handled(cardID);
}
