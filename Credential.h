#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#include "SHA256.h"

#include <QVariant>

class Credential
{
	friend class Settings;

public:
	Credential() = default;
	Credential(QString username, QString password);

	void SetUsername(QString username);
	void SetPassword(QString password);
	void SetEncryptedPassword(QString password);
	bool Authenticate(QString username, QString password);

private:
	QString username;
	QString passwordHash;
};

#endif