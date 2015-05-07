#ifndef SETTINGS_H
#define SETTINGS_H

#include "Stadium.h"
#include "Credential.h"

#include <QVariant>
#include <QJsonObject>
#include <QSettings>
#include <QStandardPaths>

class Settings
{
public:
	Settings();

	bool LoadCredentials();
	void SaveCredentials();

	Credential adminLogin;

private:
	const QString CompanyName = "ScrumShot";
	const QString ProductName = "StadiumTripPlanner";
	const QString UsernamePath = "Login/Username";
	const QString PasswordPath = "Login/Password";
	const QString DataFilePath = "/StadiumTripPlanner/StadiumData.json";

	QSettings qSettings;
	QString   dataFile;
};

extern Settings AppSettings;

#endif