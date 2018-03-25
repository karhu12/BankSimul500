#include "dllmysql.h"


DLLMySql::DLLMySql() : database(new Database), file(new File) {}

DLLMySql::~DLLMySql() {
    delete database;
    delete file;
    database = nullptr;
    file = nullptr;
}

bool DLLMySql::setup() {
    file->readDatabaseConfig();
    file->returnParameter("dbHostName");
    file->returnParameter("dbName");
    file->returnParameter("dbUserName");
    file->returnParameter("dbPassword");
}
