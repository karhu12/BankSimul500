#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QStringList>
#include <QDebug>

enum accountEnums { account_id = 0, firstname = 1, surname = 2, balance = 3, address = 4, post_number = 5, phone_number = 6 };
enum transactionEnums { transaction_date = 0, recipient = 1, type = 2, transaction_sum = 3 };


class Session {
public:
	bool isAccountsPinCode(QString userInput);
	void setAccountId(int id) { accountId = id; }
	void setPinCode(QString pin) { pinCode = pin; }
	void setAccountInformation(QStringList list) { accountInformation = list; }
	int setTransactions(QStringList list);
	int getAccountId() { return accountId; }
	QString getFieldFromAccount(int fieldName);
	QString getFieldFromTransaction(int fieldName, int latestTransaction);

private:
	int accountId;
	QString pinCode;
	QStringList accountInformation;
	QStringList transactions;
};

#endif // SESSION_H
