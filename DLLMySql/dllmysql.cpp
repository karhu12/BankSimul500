#include "dllmysql.h"


DLLMySql::DLLMySql() :
	database(new Database),
	file(new File) {
}

DLLMySql::~DLLMySql() {
    delete database;
    delete file;
    database = nullptr;
    file = nullptr;
}

bool DLLMySql::setup() {
	if (file->readDatabaseConfig() &&
		database->setVariable("dbHost", file->returnCommandValue("dbHost")) &&
		database->setVariable("dbUser", file->returnCommandValue("dbUser")) &&
		database->setVariable("dbName", file->returnCommandValue("dbName")) &&
		database->setVariable("dbPassword", file->returnCommandValue("dbPassword")) &&
		database->connectToDatabase()) {
		return true;
	}
	else {
		return false;
	}
}
