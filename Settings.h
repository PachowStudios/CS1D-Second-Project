#ifndef SETTINGS_H
#define SETTINGS_H

#include "Stadium.h"
#include "Souvenir.h"
#include "Credential.h"
#include "Graph.h"

#include <QVariant>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>
#include <QStandardPaths>
#include <QFile>
#include <QDir>

class Settings
{
public:
	enum SearchBy
	{
		ID,
		Name,
		Team
	};

	Settings();

	bool      HasStadium(SearchBy searcyBy, QString searchTerm) const;
	Stadium&  GetStadium(SearchBy searchBy, QString searchTerm);
	bool      HasSouvenir(QString name) const;
	Souvenir& GetSouvenir(QString name);

	bool LoadCredentials();
	bool SaveCredentials();

	bool LoadStadiums(QString fileName = nullptr);
	bool SaveStadiums();

	Credential   adminLogin;
	StadiumList  stadiums;
	Graph        stadiumGraph;
	SouvenirList souvenirs;

private:
	const QString CompanyName = "ScrumShot";
	const QString ProductName = "StadiumTripPlanner";
	const QString UsernamePath = "Login/Username";
	const QString PasswordPath = "Login/Password";
	const QString DataFileFolder = "/StadiumTripPlanner/";
	const QString DataFileName = "StadiumData.json";

	QSettings qSettings;
	QString   dataFilePath;
	QString   dataFile;
};

extern Settings AppSettings;

#endif