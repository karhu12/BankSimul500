#include "servicefee.h"

void ServiceFee::startServiceFee() {
	timer = new Timer;
	connect(timer, SIGNAL(passToServiceFee(unsigned int,double)), this, SLOT(handleTimerSignal(unsigned int,double)));
}

bool ServiceFee::stopServiceFee() {
	disconnect();
	bool isOver = timer->isOverFeeLevel();
	delete timer;
	timer = nullptr;
	return isOver;
}

void ServiceFee::handleTimerSignal(unsigned int duration, double fee) {
	emit passServiceFee(duration, fee);
}

bool ServiceFee::isFeeOverBalance(double balance) {
	return timer->isFeeOverBalance(balance);
}

bool ServiceFee::isOverFeeLevel() {
	return timer->isOverFeeLevel();
}
