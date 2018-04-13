#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QStringList>
#include <QDebug>

enum accountEnums { account_id = 0, firstname, surname, balance, address, post_number, phone_number };
enum transactionEnums { transaction_date = 0, recipient, type, transaction_sum };

class Session {
public:
	void setAccountInformation(QStringList list) { accountInformation = list; }
	bool setSessionData(QStringList list, QString card);
	int setTransactions(QStringList list);
	int getAccountId() const { return accountId; }
	QString getCardNumber() const { return cardNumber; }
	bool isAccountsPinCode(QString userInput);
	bool isValidTransaction(QString sum);
	QString getFieldFromAccount(int fieldName) const;
	QString getFieldFromTransaction(int fieldName, int latestTransaction) const;
	void createTransactionStrings(QString &dateStr, QString &typeStr, QString &recipientStr, QString &sumStr, int page);
	void createTransactionStrings(QString &dateStr, QString &typeStr, QString &recipientStr, QString &sumStr, int start, int end);


private:
	static int accountId;
	static QString pinCode, cardNumber;
	static QStringList accountInformation, transactions;
};

#endif // SESSION_H
