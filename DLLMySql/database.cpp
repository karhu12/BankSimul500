#include "database.h"

//Opens connection to database with given parameters from connection.cfg file
bool Database::connectToDatabase() {
    db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(dbHost); //dbHost
	db.setDatabaseName(dbName); //dbName
	db.setUserName(dbUser); //dbUser
	db.setPassword(dbPassword); //dbPassword
    if (db.open()) {
		qDebug() << "Opened connection";
		query = new QSqlQuery;
        return true;
    }
    else {
		qDebug() << "No connection to db";
        return false;
    }
}

//Checks if database connection is open
bool Database::isConnected() {
	return db.open();
}

//Sulkee yhteyden tietokantaan ja palauttaa true jos sulkeminen onnistui
bool Database::closeConnection() {
	delete query;
	query = nullptr;
	db.close();
	if (isConnected())
		return false;
	else
		return true;
}

//General setter for database QStrings. If variable exists update it with new value.
bool Database::setVariable(QString variableName, QString value) {
	if (variableName == "dbHost") {
		dbHost = value;
	}
	else if (variableName == "dbUser") {
		dbUser = value;
	}
	else if (variableName == "dbName") {
		dbName = value;
	}
	else if (variableName == "dbPassword") {
		dbPassword = value;
	}
	else {
		qDebug() << "Failure setting given variable name with value.";
		return false;
	}
	return true;
}

bool Database::startTransaction() {
	return db.transaction();
}

bool Database::commitTransaction() {
	return db.commit();
}

bool Database::rollbackTransaction() {
	return db.rollback();
}
