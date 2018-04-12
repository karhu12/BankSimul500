#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QDebug>

class Database {
public:
    bool connectToDatabase();
	bool connectToDatabaseDefault();
	void closeConnection();
	bool setVariable(QString variableName, QString value);
	QStringList getCardFromNumber(QString cardNumber);
	QStringList getAccountInformation(int accountId);
	QStringList getTransactions(int accountId);
	bool getCardLockedState(QString cardNumber);
	bool lockCard(QString cardNumber);
	bool chargePayment(float sum, float balance, int accountId);
	bool receivePayment(float sum, float balance, int accountId);


private:
    QString dbHost, dbName, dbUser, dbPassword;
	QSqlDatabase db;
	QSqlQuery *query;
	bool setBalanceFromSum(float sum, int accountId);
	bool createTransactionFromSum(float sum, int accountId, char type);
};

//QSqlDatabase Database::db;

#endif // DATABASE_H
