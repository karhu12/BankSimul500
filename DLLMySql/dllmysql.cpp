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
	if (!result.empty()) {
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

//Palauttaa nykyisen kirjautuneen tilin tilitapahtumien määrän ja tallentaa ne paikalliseen sessio listaan
//TÄYTYY KUTSUA ENNEN sql->getTransactionField():n KÄYTTÖÄ!!!
//Voit hakea tilitapahtuman tietoja käyttämällä sql->getTransactionField() funktiota
int DLLMySql::getLastTransactions() {
	return session->setTransactions(database->getTransactions(session->getAccountId()));
}

/*Palauttaa QString tyyppisenä halutun tilitapahtuman tiedon
*Voit hakea fieldNamen parametrinä jotain näistä: transaction_date, recipient, type, transaction_sum
*latestTransaction parametri tarkoittaa kuinka uutta tilitapahtumaa haetaan. 0 uusin -> 1 yhden vahempi 2 -> vanhempi... jne...
*tämän kanssa on avuliasta käyttää getLatestTransaction() funktion palauttamaa numeroa, että tietää paljonko tapahtumia on kokonaisuudessaan

QString DLLMySql::getTransactionField(int fieldName, int latestTransaction) {
	return session->getFieldFromTransaction(fieldName,latestTransaction);
} POIS KÄYTÖSTÄ */


//Luo tilitapahtumia varten tehdyt QStringit. Sijoitetaan halutut stringit parametreiksi ja valitaan mistä kohtaa tilitapahtumia haetaan.
//ESIM. createTransactionStrings(dateString,typeString,recipientString,sumString,0,9); hakisi uusimmat 10 tilitapahtumaa ja sijoittaisi ne haluttuihin stringeihin.
void DLLMySql::createTransactionStrings(QString &dateString, QString &typeString, QString &recipientString, QString &sumString, int start, int end) {
	dateString = ""; typeString = ""; recipientString = ""; sumString = "";
	for (int i = start; i < end; ++i) {
		if (session->getFieldFromTransaction(type,i) != "") {
			dateString += session->getFieldFromTransaction(transaction_date,i) + "\n\n";
			typeString += session->getFieldFromTransaction(type,i) + "\n\n";
			recipientString += session->getFieldFromTransaction(recipient,i) + "\n\n";
			sumString += session->getFieldFromTransaction(transaction_sum,i) + "€\n\n";
		}
	}
}
