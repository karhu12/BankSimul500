#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "dllmysql_global.h"
#include "database.h"
#include "file.h"
#include <QtSql>

class DLLMYSQLSHARED_EXPORT DLLMySql {
public:
    DLLMySql();
    ~DLLMySql();
    bool setup();

private:
    Database *database;
    File *file;
};

#endif // DLLMYSQL_H
