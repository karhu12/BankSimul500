#ifndef QUERY_H
#define QUERY_H

#include <QSqlQuery>
#include <QDebug>

class Query {
public:
	QStringList getCardFromNumber(QString cardNumber);
	QStringList getAccountInformation(int accountId);
	QStringList getTransactions(int accountId);

protected:
	QSqlQuery *query;
};

#endif // QUERY_H
