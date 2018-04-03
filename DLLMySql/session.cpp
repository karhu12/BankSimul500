#include "session.h"

bool Session::isAccountsPinCode(QString userInput) {
	if (userInput == pinCode)
		return true;
	else
		return false;
}

QString Session::getFieldFromAccount(int fieldName) {
	return accountInformation.at(fieldName);
}


QString Session::getFieldFromTransaction(int fieldName, int latestTransaction) {
	int i = (latestTransaction * 4) + fieldName;
	return transactions.value(i);
}
