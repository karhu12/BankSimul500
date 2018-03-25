#include "database.h"

Database::Database() {
}

Database::~Database() {
}

bool Database::connectToDatabase() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dbHost);
    db.setDatabaseName(dbName);
    db.setUserName(dbUser);
    db.setPassword(dbPassword);
    if (db.open()) {
        return true;
    }
    else {
        return false;
    }
}
