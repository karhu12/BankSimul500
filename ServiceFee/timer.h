#ifndef TIMER_H
#define TIMER_H
#define FEE_PER_SEC 1 //€ / sekunti

#include <QTimer>
#include <QDebug>

class Timer : public QObject
{
	Q_OBJECT

public:
	Timer();
	~Timer();
	double getTotalFee();
	bool isFeeOverBalance(double balance);
	bool isOverFeeLevel();

private slots:
	void timeoutHandle();

signals:
	passToServiceFee(unsigned int duration, double fee);

private:
	QTimer *timer;
	unsigned int duration;
	double totalFee;
};

#endif // TIMER_H
