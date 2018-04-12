#ifndef DLLSERIALPORT_ENGINE_H
#define DLLSERIALPORT_ENGINE_H
#include <QString>
#include <QtSerialPort/QSerialPort>


class DLLSerialPort_engine : public QObject
{
    Q_OBJECT
public:
    DLLSerialPort_engine();

private:
    QSerialPort *serial;

public slots:
    void handleSignal();

signals:
    handled(QString ID);
};

#endif // DLLSERIALPORT_ENGINE_H
