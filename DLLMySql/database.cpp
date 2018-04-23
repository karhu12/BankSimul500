#include "database.h"

QSqlDatabase Database::db;
QString Database::dbName, Database::dbHost, Database::dbPassword, Database::dbUser;
QSqlQuery Database::query;
bool Database::connected = false;

//Avaa yhteyden tietokantaan connection.cfg tiedoilla.
bool Database::connectToDatabase() {
	if (!connected) {
		db = QSqlDatabase::addDatabase("QMYSQL", "defaultConnection");
		db.setHostName(dbHost); //dbHost
		db.setDatabaseName(dbName); //dbName
		db.setUserName(dbUser); //dbUser
		db.setPassword(dbPassword); //dbPassword
		if (db.open()) {
			qDebug() << "Opened connection";
			//query = new QSqlQuery(db);
			query = QSqlQuery(db);
			connected = true;
			return true;
		}
		else {
			qDebug() << "No connection to db";
			connected = false;
			return false;
		}
	}
	else {
		qDebug() << "can't connect to db while connected!";
		return false;
	}
}

//Avaa yhteyden tietokantaan perusparametreillä
bool Database::connectToDatabaseDefault() {
	if (!connected) {
		db = QSqlDatabase::addDatabase("QMYSQL", "defaultConnection");
		db.setHostName("mysli.oamk.fi"); //dbHost
		db.setDatabaseName("opisk_t6kari01"); //dbName
		db.setUserName("t6kari01"); //dbUser
		db.setPassword("5JqdbY8ekp9yPzjR"); //dbPassword
		if (db.open()) {
			qDebug() << "Opened connection";
			//query = new QSqlQuery(db);
			query = QSqlQuery(db);
			connected = true;
			return true;
		}
		else {
			qDebug() << "No connection to db";
			connected = false;
			return false;
		}
	}
	else {
		qDebug() << "Can't connect while connected!";
		return false;
	}
}

//Sulkee yhteyden tietokantaan ja palauttaa true jos sulkeminen onnistui
void Database::closeConnection() {
	if (connected) {
		db.close();
		db = QSqlDatabase();
		db.removeDatabase("defaultConnection");
		connected = false;
		qDebug() << "Connection closed...";
	}
	else {
		qDebug() << "No connection to close...";
	}
	//delete query;
	//query = nullptr;
}

//Muuttuja setteri, jos muuttuja nimi on olemassa arvo asetetaan valueksi ja palautetaan true
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

//Aloittaa tietokanta transactionin ja yrittää päivittää tilin saldon ja luoda tilitapahtuman. Jos menee läpi tietokannalle tehdään commit ja palautetaan true.
//Muuten tietokanta rollback ja palautetaan false. QStringi parametrinä asettaa transactioniin halutun nimen
bool Database::chargePayment(float sum, float balance, int accountId, QString type, QString receiver) {
	db.transaction();
	if (setBalanceFromSum(balance - sum, accountId)) {
        if (createTransactionFromSum(sum, accountId, '-', type, receiver)) {
			db.commit();
			return true;
		}
		else {
			qDebug() << "Tilitapahtuman luonti epäonnistui...";
			db.rollback();
			return false;
		}
	}
	else {
		qDebug() << "Tilin saldon asetus epäonnistui...";
		db.rollback();
		return false;
	}
}

//Toimii kuin ylempi funktio, mutta veloittamisen sijasta rahaa tulee tilille.
bool Database::receivePayment(float sum, float balance, int accountId, QString type, QString receiver) {
	if (sum != 0) {
		db.transaction();
		if (setBalanceFromSum(sum + balance, accountId)) {
            if (createTransactionFromSum(sum, accountId, '+', type, receiver)) {
				db.commit();
				return true;
			}
			else {
				qDebug() << "Tilitapahtuman luonti epäonnistui...";
				db.rollback();
				return false;
			}
		}
		else {
			qDebug() << "Tilin saldo asetus epäonnistui...";
			db.rollback();
			return false;
		}
	}
	else {
		return false;
	}
}

//Palauttaa kyselyn tuloksen jos kortti löyty halutulla kortin numerolla
QStringList Database::getCardFromNumber(QString cardNumber) {
	query.prepare("SELECT account_id, pin_code FROM Card where card_number = ?;");
	query.addBindValue(cardNumber);
	query.exec();
	QStringList queryResult;
	if (query.size() > 0) {
		query.first();
		queryResult.push_back(query.value(0).toString()); //account_id
		queryResult.push_back(query.value(1).toString()); //pin_code
	}
	return queryResult;
}

//Palauttaa tilin ja asiakkaan tiedot halutulla tilinumerolla
QStringList Database::getAccountInformation(int accountId) {
	QStringList queryResult;
	query.prepare("SELECT account_number, firstname, surname, cast(balance as signed), address, post_number, phone_number "
				"FROM Account INNER JOIN Client ON Client.client_id = Account.client_id "
				"WHERE account_id = ?;");
	query.addBindValue(accountId);
	query.exec();
	if (query.size() > 0) {
		query.first();
		queryResult.push_back(query.value(0).toString()); //account_number
		queryResult.push_back(query.value(1).toString()); //firstname
		queryResult.push_back(query.value(2).toString()); //surname
		queryResult.push_back(query.value(3).toString()); //balance
		queryResult.push_back(query.value(4).toString()); //address
		queryResult.push_back(query.value(5).toString()); //post_number
		queryResult.push_back(query.value(6).toString()); //phone_number
	}
	return queryResult;
}

//Hakee kaikki halutun tilin tilitapahtumat ja palauttaa ne
QStringList Database::getTransactions(int accountId) {
	QStringList queryResult;
	query.prepare("SELECT DATE_FORMAT(transaction_date, '%d.%m'), recipient, type, transaction_sum "
				"FROM Transaction WHERE account_id = ? ORDER BY transaction_date DESC");
	query.addBindValue(accountId);
	query.exec();
	if (query.size() > 0) {
		while (query.next()) {
			queryResult.push_back(query.value(0).toString()); //transaction_date
			queryResult.push_back(query.value(1).toString()); //recipient
			queryResult.push_back(query.value(2).toString()); //type
			queryResult.push_back(query.value(3).toString()); //transaction_sum
		}
	}
	return queryResult;
}

bool Database::getCardLockedState(QString cardNumber) {
	query.prepare("SELECT cast(locked as unsigned) FROM Card where card_number = ?;");
	query.addBindValue(cardNumber);
	query.exec();
	query.first();
	return query.value(0).toBool();
}

//Päivittää halutun tilin saldon tietyksi
bool Database::setBalanceFromSum(float sum, int accountId) {
	query.prepare("UPDATE Account SET balance = ? where account_id = ?;");
	query.addBindValue(sum);
	query.addBindValue(accountId);
	return query.exec();
}


//Luo tilitapahtuman halutusta tilistä Perustyypillä: saaja - Pankki, tyyppi - transType ja parametrinä pano(+) vai nosto(-)
bool Database::createTransactionFromSum(float sum, int accountId, char type, QString transType, QString receiver) {
    if (sum > 0) {
        return query.exec("INSERT INTO Transaction (account_id, type, transaction_sum, recipient, transaction_date)"
                           "VALUES(" + QString::number(accountId) + ", \"" + transType + "\", " + (type == '+' ? "+" : "-") + QString::number(sum) + ", "
                           "\"" + receiver + "\", now());");
    }
    return true;
}

//Poistaa halutun kortin tietokannasta tilinumeron perusteella
bool Database::lockCard(QString cardNumber) {
	query.prepare("UPDATE Card SET locked = 1 where card_number = ?;");
	query.addBindValue(cardNumber);
	return query.exec();
}
