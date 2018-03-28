#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QRegExp>

class File {
public:
    bool readDatabaseConfig();
	QString returnCommandValue(QString command);

private:
    QStringList commands, parameters;
};

#endif // FILE_H
