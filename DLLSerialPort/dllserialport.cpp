#include "dllserialport.h"


DLLSerialPort::DLLSerialPort() {
    objectDLLSerialPort_engine = new DLLSerialPort_engine;
    QObject::connect(objectDLLSerialPort_engine, SIGNAL(handled(QString)),
                     this, SLOT(recieveSignal(QString)));
}

DLLSerialPort::~DLLSerialPort() {
    delete objectDLLSerialPort_engine;
}

void DLLSerialPort::recieveSignal(QString ID) {
    emit passID(ID);
}
