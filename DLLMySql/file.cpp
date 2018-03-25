#include "file.h"

bool File::readDatabaseConfig() {
    QString command, parameter, data, path = QDir::currentPath();
    path += "/connection.cfg";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Read failure";
        qDebug() << path;
        return false;
    }

    while (!file.atEnd()) {
        data = file.readLine();
        if (data.indexOf("=") >= 0) {
            command = data.split("=").at(0);
            parameter = data.split("=").at(1);
            commands.push_back(command);
            parameters.push_back(parameter);
        }
    }
    return true;
}

QString File::returnParameter(QString command) {
    for (int i = 0; i < commands.size(); ++i) {
        if (QString::compare(command, commands.at(i), Qt::CaseSensitive) == 0) {
            qDebug() << parameters.at(i);
            return parameters.at(i);
        }
    }
}
