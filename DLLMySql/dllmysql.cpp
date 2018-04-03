#include "dllmysql.h"


DLLMySql::DLLMySql() :
	database(new Database),
	file(new File),
	session(new Session) {
}

DLLMySql::~DLLMySql() {
    delete database;
    delete file;
	delete session;
    database = nullptr;
    file = nullptr;
	session = nullptr;
}

//Start connection with the database true if succsefull
bool DLLMySql::setup() {
	if (file->readDatabaseConfig() &&
		database->setVariable("dbHost", file->returnCommandValue("dbHost")) &&
		database->setVariable("dbUser", file->returnCommandValue("dbUser")) &&
		database->setVariable("dbName", file->returnCommandValue("dbName")) &&
		database->setVariable("dbPassword", file->returnCommandValue("dbPassword")) &&
		database->connectToDatabase()
	)
		return true;
	else
		return false;
}

//Palauttaa True jos anetulla korttinumerolla on tili liitettynä
bool DLLMySql::findAccountWithCardNumber(QString cardNumber) {
	QStringList result = database->getCardFromNumber(cardNumber);
	//If resulted query is not empty found an card with cardNumber and account
	if (!result.empty()) {
		//Save account_id and pin_code for later use
		session->setAccountId(result.at(0).toInt());
		session->setPinCode(result.at(1));
		return true;
	}
	else {
		return false;
	}
}

//Palauttaa True jos pin koodi on sama kuin kortille liitetty pin koodi
bool DLLMySql::confirmAccountPin(QString pinCode) {
	if (session->isAccountsPinCode(pinCode)) {
		session->setAccountInformation(database->getAccountInformation(session->getAccountId()));
		return true;
	}
	else
		return false;
}

//Palauttaa halutun tilin tiedon, käytä jotakin seuraavista parametreistä
//account_id, firstname, surname, balance, address, post_number, phone_number (VOI KIRJOITTAA SUORAAN!)
//esim. sql->getAccountInformation(surname);
QString DLLMySql::getAccountInformation(int fieldName) {
	return session->getFieldFromAccount(fieldName);
}

void DLLMySql::getLastTransactions(int amount) {
	session->setTransactions(database->getAmountOfTransactions(amount, session->getAccountId()));
}

QString DLLMySql::getTransactionField(int fieldName, int latestTransaction) {
	return session->getFieldFromTransaction(fieldName,latestTransaction);
}

