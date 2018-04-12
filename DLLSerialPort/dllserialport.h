#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include "dllserialport_global.h"
#include "dllserialport_engine.h"
#include <QString>

class DLLSERIALPORTSHARED_EXPORT DLLSerialPort : public QObject
{
Q_OBJECT
public:
    DLLSerialPort();
    ~DLLSerialPort();
private:
    DLLSerialPort_engine *objectDLLSerialPort_engine;

public slots:
    void recieveSignal(QString ID);

signals:
    passID(QString ID);

};

#endif // DLLSERIALPORT_H
