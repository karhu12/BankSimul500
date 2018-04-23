#include "servicefee.h"

//Palvelumaksun käynnistys. Yhdistä passServiceFee(unsigned, double) signaali haluttuun slot funktioon jotta voit käsitellä ajastimen viestejä.
void ServiceFee::startServiceFee() {
	timer = new Timer;
	connect(timer, SIGNAL(passToServiceFee(unsigned int,double)), this, SLOT(handleTimerSignal(unsigned int,double)));
}

//Palvelumaksun lopetus. Palauttaa true/false menikö aikaa tarpeeksi ylittääksemme 20s maksu raja
bool ServiceFee::stopServiceFee() {
	disconnect(this);
	bool isOver = timer->isOverFeeLevel();
	delete timer;
	timer = nullptr;
	return isOver;
}

//Välittää palvelumaksun keston ja maksun
void ServiceFee::handleTimerSignal(unsigned int duration, double fee) {
	emit passServiceFee(duration, fee);
}

//Palauttaa true jos tilin saldo on pienempi kuin palvelumaksu
bool ServiceFee::isFeeOverBalance(double balance) {
	return timer->isFeeOverBalance(balance);
}
