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
    bool chargePayment(float sum, float balance, int accountId, QString type, QString receiver);
    bool receivePayment(float sum, float balance, int accountId, QString type, QString receiver);


private:
	static bool connected;
	static QString dbHost, dbName, dbUser, dbPassword;
	static QSqlDatabase db;
	static QSqlQuery query;
	bool setBalanceFromSum(float sum, int accountId);
    bool createTransactionFromSum(float sum, int accountId, char type, QString transType, QString receiver);
};

//QSqlDatabase Database::db;

#endif // DATABASE_H
