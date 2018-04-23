#include "timer.h"

Timer::Timer() {
	timer = new QTimer;
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeoutHandle()));
	totalFee = 20;
	duration = 0;
	qDebug() << "Service fee started";
}

Timer::~Timer() {
	disconnect(timer);
	delete timer;
	timer = nullptr;
}

void Timer::timeoutHandle() {
	emit passToServiceFee(duration, totalFee);
	if (duration >= 20) {
		totalFee += FEE_PER_SEC;
	}
	else {
		totalFee -= FEE_PER_SEC;
	}
	++duration;
}

double Timer::getTotalFee() {
	if (duration <= 20) {
		return 20 - duration;
	}
	else {
		return -totalFee;
	}
}

bool Timer::isFeeOverBalance(double balance) {
	if (duration > 20)
		if (totalFee >= balance)
			return true;
		else
			return false;
	else
		return false;
}

bool Timer::isOverFeeLevel() {
	if (duration  > 20)
		return true;
	else
		return false;
}
