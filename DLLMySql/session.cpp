#include "session.h"

int Session::accountId;
QString Session::pinCode, Session::cardNumber;
QStringList Session::accountInformation, Session::transactions;

//Palauttaa true jos parametri pin koodi on sama kuin kortin oma pin koodi
bool Session::isAccountsPinCode(QString userInput) {
	if (userInput == pinCode)
		return true;
	else
		return false;
}

//Palauttaa halutun tiedon tililtä jotka tallennettiin kirjautumisen yhteydessä
//Käytä seuraavia parametrejä: firstname, surname, balance, account_id, address, post_number, phone_number
QString Session::getFieldFromAccount(int fieldName) const {
	return accountInformation.at(fieldName);
}


QString Session::getFieldFromTransaction(int fieldName, int latestTransaction) const {
	int i = (latestTransaction * 4) + fieldName;
	return transactions.value(i);
}

int Session::setTransactions(QStringList list) {
	transactions = list;
	return transactions.size() / 4;
}

bool Session::isValidTransaction(QString sum) {
    if (accountInformation.size() > 0) {
        if (getFieldFromAccount(balance).toFloat() - sum.toFloat() >= 0)
            return true;
        else
            return false;
    }
    return false;
}

bool Session::setSessionData(QStringList list, QString card) {
	if (list.size() > 0) {
		accountId = list.at(0).toInt();
		pinCode = list.at(1);
		cardNumber = card;
		return true;
	}
	else {
		return false;
	}
}

void Session::createTransactionStrings(QString &dateStr, QString &typeStr, QString &recipientStr, QString &sumStr, int start, int end) {
	dateStr = ""; typeStr = ""; recipientStr = ""; sumStr = "";
	for (int i = start; i <= end; ++i) {
		if (getFieldFromTransaction(type,i) != "") {
			dateStr += getFieldFromTransaction(transaction_date,i) + "\n\n";
			typeStr += getFieldFromTransaction(type,i) + "\n\n";
			recipientStr += getFieldFromTransaction(recipient,i) + "\n\n";
			sumStr += getFieldFromTransaction(transaction_sum,i) + "€\n\n";
		}
	}
}

void Session::createTransactionStrings(QString &dateStr, QString &typeStr, QString &recipientStr, QString &sumStr, int page) {
	dateStr = ""; typeStr = ""; recipientStr = ""; sumStr = "";
	int start = 0 + (page * 10), end = 9 + (page * 10);
	for (int i = start; i <= end; ++i) {
		if (getFieldFromTransaction(type,i) != "") {
			dateStr += getFieldFromTransaction(transaction_date,i) + "\n\n";
			typeStr += getFieldFromTransaction(type,i) + "\n\n";
			recipientStr += getFieldFromTransaction(recipient,i) + "\n\n";
			sumStr += getFieldFromTransaction(transaction_sum,i) + "€\n\n";
		}
	}
}
