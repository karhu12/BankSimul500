#include "file.h"

//Used to read connection.cfg in project directory to setup database info on startup
bool File::readDatabaseConfig() {
	QString command, parameter, data;
	QDir path;
	QFile file(path.absolutePath() + "/connection.cfg");
    if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "Config file read failure...";
        return false;
    }
	//read all commands and their parameters. Remove all escape characters and whitespaces from them
    while (!file.atEnd()) {
        data = file.readLine();
        if (data.indexOf("=") >= 0) {
            command = data.split("=").at(0);
            parameter = data.split("=").at(1);
			command.simplified();
			command.replace(" ","");
			command.remove(QRegExp("[\\r\\n]"));
			parameter.simplified();
			parameter.replace(" ","");
			parameter.remove(QRegExp("[\\r\\n]"));
			//Store them in QStringLists
            commands.push_back(command);
			parameters.push_back(parameter);
		}
    }
	qDebug() << "Finished reading config file...";
    return true;
}

//Returns parameter value of given command if it existed in connection.cfg file
QString File::returnCommandValue(QString command) {
	for (int i = 0; i < commands.size(); ++i) {
		if (QString::compare(command, commands.at(i), Qt::CaseSensitive) == 0) {
            return parameters.at(i);
        }
    }
	qDebug() << "Failure finding value for command";
	return "";
}
