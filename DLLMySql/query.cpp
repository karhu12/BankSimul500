#include "query.h"

QStringList Query::getCardFromNumber(QString cardNumber) {
	query->exec("SELECT account_id, pin_code FROM Card where card_number = \"" + cardNumber + "\"");
	QStringList queryResult;
	if (query->size() > 0) {
		query->first();
		queryResult.push_back(query->value(0).toString()); //account_id
		queryResult.push_back(query->value(1).toString()); //pin_code
	}
	return queryResult;
}

QStringList Query::getAccountInformation(int accountId) {
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

QStringList Query::getTransactions(int accountId) {
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

bool Query::setBalanceFromSum(float sum, int accountId) {
	return query->exec("UPDATE Account SET balance = " + QString::number(sum) + " where account_id = " + QString::number(accountId) + ";");
}

bool Query::createTransactionFromSum(float sum, int accountId) {
	return query->exec("INSERT INTO Transaction (account_id, type, transaction_sum, recipient, transaction_date)"
					   "VALUES(" + QString::number(accountId) + ", \"TILISIIRTO\", -" + QString::number(sum) + ", "
					   "\"Pankki\", now());");
}

bool Query::removeCard(QString cardNumber) {
	return query->exec("DELETE FROM Card where card_number = \"" + cardNumber + "\";");
}
