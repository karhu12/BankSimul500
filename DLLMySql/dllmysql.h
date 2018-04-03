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
	void getLastTransactions(int amount);
	QString getTransactionField(int fieldName, int latestTransaction);

private:
    Database *database;
    File *file;
	Session *session;
};

#endif // DLLMYSQL_H
