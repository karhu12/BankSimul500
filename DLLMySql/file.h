#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QDebug>
#include <QDir>
#include <QString>

class File {
public:
    bool readDatabaseConfig();
    QString returnParameter(QString command);

private:
    QStringList commands, parameters;
};

#endif // FILE_H
