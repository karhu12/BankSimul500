#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QDebug>

class Database {
public:
    bool connectToDatabase();
	bool isConnected();
	void closeConnection();
	bool setVariable(QString variableName, QString value);

private:
    QString dbHost, dbName, dbUser, dbPassword;
    QSqlDatabase db;
};

#endif // DATABASE_H
