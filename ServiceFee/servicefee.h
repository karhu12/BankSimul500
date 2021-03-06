#ifndef SERVICEFEE_H
#define SERVICEFEE_H

#include "servicefee_global.h"
#include "timer.h"

class SERVICEFEESHARED_EXPORT ServiceFee : public QObject
{
	Q_OBJECT
public:
	void startServiceFee();
	bool stopServiceFee();
	bool isFeeOverBalance(double balance);


signals:
	passServiceFee(unsigned int duration, double fee);

private slots:
	void handleTimerSignal(unsigned int duration, double fee);

private:
	Timer *timer;
};

#endif // SERVICEFEE_H
