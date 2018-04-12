#include "database.h"

//Avaa yhteyden tietokantaan connection.cfg tiedoilla.
bool Database::connectToDatabase() {
	db = QSqlDatabase::addDatabase("QMYSQL", "defaultConnection");
	qDebug() << db.connectionName();
	db.setHostName(dbHost); //dbHost
	db.setDatabaseName(dbName); //dbName
	db.setUserName(dbUser); //dbUser
	db.setPassword(dbPassword); //dbPassword
    if (db.open()) {
		qDebug() << "Opened connection";
		query = new QSqlQuery(db);
        return true;
    }
    else {
		qDebug() << "No connection to db";
        return false;
    }
}

//Avaa yhteyden tietokantaan perusparametreillä
bool Database::connectToDatabaseDefault() {
	db = QSqlDatabase::addDatabase("QMYSQL", "defaultConnection");
	db.setHostName("mysli.oamk.fi"); //dbHost
	db.setDatabaseName("opisk_t6kari01"); //dbName
	db.setUserName("t6kari01"); //dbUser
	db.setPassword("5JqdbY8ekp9yPzjR"); //dbPassword
	if (db.open()) {
		qDebug() << "Opened connection";
		query = new QSqlQuery(db);
		return true;
	}
	else {
		qDebug() << "No connection to db";
		return false;
	}
}

//Sulkee yhteyden tietokantaan ja palauttaa true jos sulkeminen onnistui
void Database::closeConnection() {
	db.close();
	db = QSqlDatabase();
	db.removeDatabase("defaultConnection");
	delete query;
	query = nullptr;
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
//Muuten tietokanta rollback ja palautetaan false.
bool Database::chargePayment(float sum, float balance, int accountId) {
	db.transaction();
	if (setBalanceFromSum(balance - sum, accountId)) {
		if (createTransactionFromSum(sum, accountId, '-')) {
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
bool Database::receivePayment(float sum, float balance, int accountId) {
	db.transaction();
	if (setBalanceFromSum(sum + balance, accountId)) {
		if (createTransactionFromSum(sum, accountId, '+')) {
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

//Palauttaa kyselyn tuloksen jos kortti löyty halutulla kortin numerolla
QStringList Database::getCardFromNumber(QString cardNumber) {
	query->exec("SELECT account_id, pin_code FROM Card where card_number = \"" + cardNumber + "\"");
	QStringList queryResult;
	if (query->size() > 0) {
		query->first();
		queryResult.push_back(query->value(0).toString()); //account_id
		queryResult.push_back(query->value(1).toString()); //pin_code
	}
	return queryResult;
}

//Palauttaa tilin ja asiakkaan tiedot halutulla tilinumerolla
QStringList Database::getAccountInformation(int accountId) {
	QStringList queryResult;
	query->exec("SELECT account_number, firstname, surname, cast(balance as signed), address, post_number, phone_number "
				"FROM Account INNER JOIN Client ON Client.client_id = Account.client_id "
				"WHERE account_id = " + QString::number(accountId) + ";");
	if (query->size() > 0) {
		query->first();
		queryResult.push_back(query->value(0).toString()); //account_number
		queryResult.push_back(query->value(1).toString()); //firstname
		queryResult.push_back(query->value(2).toString()); //surname
		queryResult.push_back(query->value(3).toString()); //balance
		queryResult.push_back(query->value(4).toString()); //address
		queryResult.push_back(query->value(5).toString()); //post_number
		queryResult.push_back(query->value(6).toString()); //phone_number
	}
	return queryResult;
}

//Hakee kaikki halutun tilin tilitapahtumat ja palauttaa ne
QStringList Database::getTransactions(int accountId) {
	QStringList queryResult;
	query->exec("SELECT DATE_FORMAT(transaction_date, '%d.%m'), recipient, type, transaction_sum "
				"FROM Transaction WHERE account_id = " + QString::number(accountId) + " ORDER BY transaction_date DESC");

	if (query->size() > 0) {
		while (query->next()) {
			queryResult.push_back(query->value(0).toString()); //transaction_date
			queryResult.push_back(query->value(1).toString()); //recipient
			queryResult.push_back(query->value(2).toString()); //type
			queryResult.push_back(query->value(3).toString()); //transaction_sum
		}
	}
	return queryResult;
}

bool Database::getCardLockedState(QString cardNumber) {
	query->exec("SELECT cast(locked as unsigned) FROM Card where card_number = \"" + cardNumber + "\";");
	query->first();
	qDebug() << query->value(0).toBool() << query->value(0).toInt();
	return query->value(0).toBool();
}

//Päivittää halutun tilin saldon tietyksi
bool Database::setBalanceFromSum(float sum, int accountId) {
	return query->exec("UPDATE Account SET balance = " + QString::number(sum) + " where account_id = " + QString::number(accountId) + ";");
}

//Luo tilitapahtuman halutusta tilistä Perustyypillä: saaja - Pankki, tyyppi - TILISIIRTO ja parametrinä pano(+) vai nosto(-)
bool Database::createTransactionFromSum(float sum, int accountId, char type) {
	return query->exec("INSERT INTO Transaction (account_id, type, transaction_sum, recipient, transaction_date)"
					   "VALUES(" + QString::number(accountId) + ", \"TILISIIRTO\", " + (type == '+' ? "+" : "-") + QString::number(sum) + ", "
					   "\"Pankki\", now());");
}

//Poistaa halutun kortin tietokannasta tilinumeron perusteella
bool Database::lockCard(QString cardNumber) {
	return query->exec("UPDATE Card SET locked = 1 where card_number = \"" + cardNumber + "\";");
}
