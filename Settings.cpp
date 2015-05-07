#include "Settings.h"

Settings AppSettings;

Settings::Settings()
	: qSettings("ScrumShot", "StadiumTripPlanner")
{
	dataFile = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DataLocation)
		     + DataFilePath;
}

bool Settings::HasStadium(SearchBy searchBy, QString searchTerm) const
{
	using std::any_of;

	return any_of(stadiums.begin(),
				  stadiums.end(),
				  [searchBy, searchTerm](const Stadium &s)
	              {
					  switch (searchBy)
					  {
						  case Name: 
							  return s.name == searchTerm;
						  case Team:
							  return s.team == searchTerm;
						  default:
							  return false;
					  }
	              });
}

Stadium& Settings::GetStadium(SearchBy searchBy, QString searchTerm)
{
	using std::find_if;

	return *find_if(stadiums.begin(),
				    stadiums.end(),
				    [searchBy, searchTerm](const Stadium &s)
	                {
						switch (searchBy)
						{
							case Name:
								return s.name == searchTerm;
							case Team:
								return s.team == searchTerm;
							default:
								return false;
						}
	                });
}

bool Settings::LoadCredentials()
{
	if (qSettings.contains(UsernamePath) &&
		qSettings.contains(PasswordPath))
	{
		adminLogin.SetUsername(qSettings.value(UsernamePath).toString());
		adminLogin.SetPassword(qSettings.value(PasswordPath).toString());
	}
	else
		return false;

	return true;
}

bool Settings::SaveCredentials()
{
	qSettings.setValue(UsernamePath, adminLogin.username);
	qSettings.setValue(PasswordPath, adminLogin.passwordHash);

	return true;
}

bool Settings::LoadStadiums(QString fileName)
{
	if (fileName == nullptr)
		fileName = dataFile;

	QFile loadFile(fileName);

	if (!loadFile.open(QIODevice::ReadOnly))
		return false;

	QJsonDocument jsonDoc = QJsonDocument::fromJson(loadFile.readAll());
	QJsonArray stadiumJsonArray;
	
	if (jsonDoc.isObject() && jsonDoc.object()["Stadiums"].isArray())
		stadiumJsonArray = jsonDoc.object()["Stadiums"].toArray();
	else
		return false;

	for (int i = 0; i < stadiumJsonArray.size(); i++)
	{
		QJsonObject stadiumJson = stadiumJsonArray[i].toObject();

		if (stadiumJson.contains("Name"))
		{
			QString stadiumName = stadiumJson["Name"].toString();
			
			if (!HasStadium(SearchBy::Name, stadiumName))
			{
				Stadium stadiumObject;

				if (stadiumObject.LoadFromJson(stadiumJson))
					stadiums.append(stadiumObject);
			}
		}
	}

	return true;
}

bool Settings::SaveStadiums()
{
	QFile saveFile(dataFile);

	if (!saveFile.open(QIODevice::WriteOnly))
		return false;

	QJsonObject jsonDoc;
	QJsonArray stadiumJsonArray;

	for each (Stadium stadium in stadiums)
		stadiumJsonArray.append(stadium.SaveToJson());

	jsonDoc["Stadiums"] = stadiumJsonArray;

	saveFile.write(QJsonDocument(stadiumJsonArray).toJson());

	return true;
}