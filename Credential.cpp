#include "Credential.h"

Credential::Credential(QString username, QString password)
	: username(username)
{
	SetPassword(password);
}

void Credential::SetUsername(QString username)
{
	this->username = username;
}

void Credential::SetPassword(QString password)
{
	passwordHash = SHA256::Hash(password);
}

bool Credential::Authenticate(QString username, QString password)
{
	return username == this->username &&
		   SHA256::CompareHash(password, passwordHash);
}