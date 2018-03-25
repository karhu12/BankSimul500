#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database {
public:
    Database();
    ~Database();
    bool connectToDatabase();
    bool isConnected() {
        if (db.open()) return true;
        else return false;
    }

private:
    QString dbHost, dbName, dbUser, dbPassword;
    QSqlDatabase db;
};

#endif // DATABASE_H
