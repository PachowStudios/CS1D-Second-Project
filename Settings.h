#ifndef SETTINGS_H
#define SETTINGS_H

#include "Stadium.h"
#include "Credential.h"

#include <QVariant>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>
#include <QStandardPaths>
#include <QFile>

class Settings
{
public:
	enum SearchBy
	{
		Name,
		Team
	};

	Settings();

	bool     HasStadium(SearchBy searcyBy, QString searchTerm) const;
	Stadium& GetStadium(SearchBy searchBy, QString searchTerm);

	bool LoadCredentials();
	bool SaveCredentials();

	bool LoadStadiums(QString fileName = nullptr);
	bool SaveStadiums();

	Credential  adminLogin;
	StadiumList stadiums;

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