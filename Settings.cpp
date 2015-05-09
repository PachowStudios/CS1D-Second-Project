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
						  case ID:
							  return s.ID == searchTerm.toInt();
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
							case ID:
								return s.ID == searchTerm.toInt();
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
	QJsonObject jsonDocObject;

	if (jsonDoc.isObject())
		jsonDocObject = jsonDoc.object();
	else
		return false;

	QJsonArray stadiumJsonArray;
	QJsonArray graphJsonArray;
	
	if (jsonDocObject["Stadiums"].isArray() &&
		jsonDocObject["Graph"].isArray())
	{
		stadiumJsonArray = jsonDocObject["Stadiums"].toArray();
		graphJsonArray = jsonDocObject["Graph"].toArray();
	}
	else
		return false;

	for (auto &arrayItem : stadiumJsonArray)
	{
		QJsonObject stadiumJson = arrayItem.toObject();

		if (stadiumJson.contains("Name"))
		{
			QString stadiumName = stadiumJson["Name"].toString();
			
			if (!HasStadium(SearchBy::Name, stadiumName))
			{
				Stadium stadiumObject;

				if (stadiumObject.LoadFromJson(stadiumJson))
				{
					stadiums.append(stadiumObject);
					stadiumGraph.AddNode(stadiumObject.ID);
				}
			}
		}
	}

	for (auto &arrayItem : graphJsonArray)
	{
		QJsonObject graphLinkJson = arrayItem.toObject();

		if (graphLinkJson.contains("A") &&
			graphLinkJson.contains("B") &&
			graphLinkJson.contains("Weight"))
			stadiumGraph.SetConnection(graphLinkJson["A"].toInt(),
									   graphLinkJson["B"].toInt(),
									   graphLinkJson["Weight"].toInt());
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
	QJsonArray graphJsonArray;

	for (auto &stadium : stadiums)
		stadiumJsonArray.append(stadium.SaveToJson());



	jsonDoc["Stadiums"] = stadiumJsonArray;

	saveFile.write(QJsonDocument(jsonDoc).toJson());

	return true;
}