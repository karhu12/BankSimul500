#ifndef QUERY_H
#define QUERY_H

#include <QSqlQuery>
#include <QDebug>

class Query {
public:
	QStringList getCardFromNumber(QString cardNumber);
	QStringList getAccountInformation(int accountId);
	QStringList getTransactions(int accountId);
	bool setBalanceFromSum(float sum, int accountId);
	bool createTransactionFromSum(float sum, int accountId);
	bool removeCard(QString cardNumber);

protected:
	QSqlQuery *query;
};

#endif // QUERY_H
