#include "dllmysql.h"

DLLMySql::DLLMySql() {
	database = new Database;
	session = new Session;
}

DLLMySql::~DLLMySql() {
	delete database;
	delete session;
	database = nullptr;
	session = nullptr;
}

//Lukee connection.cfg tiedoston josta haetaan tietokannan yhdistystiedot ja yhdistetään tietokantaan.
//Jos tiedostoa ei voida lukea käytetään yhdistykseen perusparametrejä.
//Palauttaa true jos yhteys aukesi.
bool DLLMySql::setup() {
	file = new File;
	if (file->readDatabaseConfig()) {
		database->setVariable("dbHost", file->returnCommandValue("dbHost"));
		database->setVariable("dbUser", file->returnCommandValue("dbUser"));
		database->setVariable("dbName", file->returnCommandValue("dbName"));
		database->setVariable("dbPassword", file->returnCommandValue("dbPassword"));
		delete file;
		file = nullptr;
		if (database->connectToDatabase()) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		delete file;
		file = nullptr;
		if (database->connectToDatabaseDefault()) {
			return true;
		}
		else {
			return false;
		}
	}
}

//Sulkee yhteyden tietokantaan ja opistaa kaikki luodut oliot
void DLLMySql::disconnect() {
	database->closeConnection();
}

//Palauttaa True jos anetulla korttinumerolla on tili liitettynä
//Täytyy kutsua onnistuneesti ennen kuin voidaan käyttää muita sql kyselyitä, koska funktio asettaa session käyttäjän!
bool DLLMySql::findAccountWithCardNumber(QString cardNumber) {
    bool ret = session->setSessionData(database->getCardFromNumber(cardNumber), cardNumber);
    session->setAccountInformation(database->getAccountInformation(session->getAccountId()));
    return ret;
}

//Palauttaa true jos nykyinen kortti on lukittu
bool DLLMySql::isCardLocked() {
	return database->getCardLockedState(session->getCardNumber());
}

//Palauttaa True jos pin koodi on sama kuin kortille liitetty pin koodi
bool DLLMySql::confirmAccountPin(QString pinCode) {
	if (session->isAccountsPinCode(pinCode)) {
		return true;
	}
	else {
		return false;
	}
}

//Palauttaa halutun tilin tiedon, käytä jotakin seuraavista parametreistä
//account_id, firstname, surname, balance, address, post_number, phone_number
//esim. sql->getAccountInformation(surname);
QString DLLMySql::getAccountInformation(int fieldName) {
	session->setAccountInformation(database->getAccountInformation(session->getAccountId()));
	return session->getFieldFromAccount(fieldName);
}

//Palauttaa nykyisen kirjautuneen tilin tilitapahtumien määrän ja tallentaa ne staattiseen sessio listaan
//TÄYTYY KUTSUA ENNEN sql->createTransactionStrings():n KÄYTTÖÄ!!!
int DLLMySql::getLastTransactions() {
	return session->setTransactions(database->getTransactions(session->getAccountId()));
}

//Luo tilitapahtumia varten tehdyt QStringit. Sijoitetaan halutut stringit parametreiksi ja valitaan mistä kohtaa tilitapahtumia haetaan.
//ESIM. createTransactionStrings(dateString,typeString,recipientString,sumString,0,9); hakisi uusimmat 10 tilitapahtumaa ja sijoittaisi ne haluttuihin stringeihin.
//Tarkistuksen voisi tehdä esim. int start = 0, end = 9; int transAmount = getLastTransactions(); if (start + 10 < transAmount) { start += 10; end += 10; suorita; }
void DLLMySql::createTransactionStrings(QString &dateString, QString &typeString, QString &recipientString, QString &sumString, int start, int end) {
	session->createTransactionStrings(dateString, typeString, recipientString, sumString, start, end);
}

//overloaded versio aiemmasta. Tekee tilitapahtumat ns. sivun mukaan. sivu 0 (uusin) antaa 10 viimeisintä tilitapahtumaa ja sivu 1 -> 10 vanhempaa ja jne...
//Ylimeno tarkistuksen voi tehdä käyttäen getLastTransactionsin palautusarvoa jaettuna kymmenellä
//esim. int page = 0; int transAmount = getLastTransactions(); if (page + 1 < transAmount / 10) { ++page;
//createTransactionStrings(date, type, recipient, sum, page) }
void DLLMySql::createTransactionStrings(QString &dateString, QString &typeString, QString &recipientString, QString &sumString, int page) {
	session->createTransactionStrings(dateString, typeString, recipientString, sumString, page);
}

//Tarkistaa onko haluttu summa sallittu poistaa nykyiseltä tililtä ja velottaa sen sekä luo siitä tilitapahtuman
//Palautusarvoina 0 tarkoittaa onnistumista, 1 tarkoittaa että maksu oli liian suuri  ja 2 tarkoittaa että maksussa tapahtui virhe
int DLLMySql::chargePayment(float sum, QString transType, QString receiver) {
	if (session->isValidTransaction(QString::number(sum))) {
        if (database->chargePayment(sum, session->getFieldFromAccount(balance).toFloat(), session->getAccountId(), transType, receiver)) {
			session->setAccountInformation(database->getAccountInformation(session->getAccountId()));
			return 0;
		}
		else {
			return 2;
		}
	}
	else {
		return 1;
	}
}

//Lisää tilille summan verran rahaa ja luo siitä tilitapahtuman. Palauttaa true jos onnistui ongelmitta. Tilitapahtumaan tahdottu tyyppi stringinä
//Tilitapahtumaan tahdottu tyyppi stringinä
bool DLLMySql::receivePayment(float sum, QString transType, QString receiver) {
    if (database->receivePayment(sum, session->getFieldFromAccount(balance).toFloat(), session->getAccountId(), transType, receiver)) {
		session->setAccountInformation(database->getAccountInformation(session->getAccountId()));
		return true;
	}
	else {
		return false;
	}
}

//Poistaa nykyisen kirjautuneen tilin kortin tietokannasta jolloin sitä ei voi käyttää.
//Palauttaa true jos kysely meni läpi
bool DLLMySql::lockCurrentCard() {
	return database->lockCard(session->getCardNumber());
}

//Palauttaa QString tyyppisenä halutun tilitapahtuman tiedon
//Voit hakea fieldNamen parametrinä jotain näistä: transaction_date, recipient, type, transaction_sum
//latestTransaction parametri tarkoittaa kuinka uutta tilitapahtumaa haetaan. 0 uusin -> 1 yhden vahempi 2 -> vanhempi... jne...
//tämän kanssa on avuliasta käyttää getLatestTransaction() funktion palauttamaa numeroa, että tietää paljonko tapahtumia on kokonaisuudessaan
/*
QString DLLMySql::getTransactionField(int fieldName, int latestTransaction) {
	return session->getFieldFromTransaction(fieldName,latestTransaction);
}
POIS KÄYTÖSTÄ */
