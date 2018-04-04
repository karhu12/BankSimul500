#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "dllmysql_global.h"
#include "database.h"
#include "file.h"
#include "session.h"
#include <QtSql>


class DLLMYSQLSHARED_EXPORT DLLMySql {
public:
    DLLMySql();
    ~DLLMySql();
	bool setup();
	bool findAccountWithCardNumber(QString cardNumber);
	bool confirmAccountPin(QString pinCode);
	QString getAccountInformation(int fieldName);
	int getLastTransactions();
	//QString getTransactionField(int fieldName, int latestTransaction);
	void createTransactionStrings(QString &dateString, QString &typeString, QString &recipientString, QString &sumString, int start, int end);

private:
    Database *database;
    File *file;
	Session *session;
};

#endif // DLLMYSQL_H
