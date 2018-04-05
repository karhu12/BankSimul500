#include "session.h"

//Palauttaa true jos parametri pin koodi on sama kuin kortin oma pin koodi
bool Session::isAccountsPinCode(QString userInput) {
	if (userInput == pinCode)
		return true;
	else
		return false;
}

//Palauttaa halutun tiedon tililtä jotka tallennettiin kirjautumisen yhteydessä
//Käytä seuraavia parametrejä: firstname, surname, balance, account_id, address, post_number, phone_number
QString Session::getFieldFromAccount(int fieldName) {
	return accountInformation.at(fieldName);
}


QString Session::getFieldFromTransaction(int fieldName, int latestTransaction) {
	int i = (latestTransaction * 4) + fieldName;
	return transactions.value(i);
}

int Session::setTransactions(QStringList list) {
	transactions = list;
	return transactions.size() / 4;
}

bool Session::isValidTransaction(QString sum) {
	if (getFieldFromAccount(balance).toFloat() - sum.toFloat() >= 0)
		return true;
	else
		return false;
}
