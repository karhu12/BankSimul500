#ifndef DATABASE_H
#define DATABASE_H

#include "query.h"
#include <QSqlDatabase>
#include <QString>

class Database : public Query {
public:
    bool connectToDatabase();
	bool isConnected();
	bool closeConnection();
	bool setVariable(QString variableName, QString value);
	void tryQuery();
	bool startTransaction();
	bool commitTransaction();
	bool rollbackTransaction();


private:
    QString dbHost, dbName, dbUser, dbPassword;
	QSqlDatabase db;
};

#endif // DATABASE_H
