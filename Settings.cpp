#include "Settings.h"

Settings AppSettings;

Settings::Settings()
	: qSettings("ScrumShot", "StadiumTripPlanner")
{
	dataFilePath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DataLocation)
	             + DataFileFolder;
	dataFile = dataFilePath + DataFileName;
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

bool Settings::HasSouvenir(QString name) const
{
	using std::any_of;

	return any_of(souvenirs.begin(),
				  souvenirs.end(),
				  [name](const Souvenir &s)
				  { return s.name == name; });
}

Souvenir& Settings::GetSouvenir(QString name)
{
	using std::find_if;

	return *find_if(souvenirs.begin(),
					souvenirs.end(),
					[name](const Souvenir &s)
	                { return s.name == name; });
}

StadiumList Settings::PathToStadiums(Path path)
{
	StadiumList stadiumList = StadiumList();

	for each (int id in path)
		stadiumList.append(GetStadium(SearchBy::ID, QString::number(id)));

	return stadiumList;
}

bool Settings::LoadCredentials()
{
	if (qSettings.contains(UsernamePath) &&
		qSettings.contains(PasswordPath))
	{
		adminLogin.SetUsername(qSettings.value(UsernamePath).toString());
		adminLogin.SetEncryptedPassword(qSettings.value(PasswordPath).toString());
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
	QJsonArray souvenirJsonArray;
	QJsonArray graphJsonArray;
	
	if (jsonDocObject["Stadiums"].isArray()  &&
		jsonDocObject["Souvenirs"].isArray() &&
		jsonDocObject["Graph"].isArray())
	{
		stadiumJsonArray  = jsonDocObject["Stadiums"].toArray();
		souvenirJsonArray = jsonDocObject["Souvenirs"].toArray();
		graphJsonArray    = jsonDocObject["Graph"].toArray();
	}
	else
		return false;

	for (auto &arrayItem : stadiumJsonArray)
	{
		QJsonObject stadiumJson = arrayItem.toObject();
		Stadium stadiumObject;

		if (stadiumObject.LoadFromJson(stadiumJson) && !HasStadium(SearchBy::Name, stadiumObject.name))
		{
			stadiums.append(stadiumObject);
			stadiumGraph.AddNode(stadiumObject.ID);
		}
		else
			return false;
	}

	for (auto &arrayItem : souvenirJsonArray)
	{
		QJsonObject souvenirJson = arrayItem.toObject();
		Souvenir souvenirObject;

		if (souvenirObject.LoadFromJson(souvenirJson) && !HasSouvenir(souvenirObject.name))
			souvenirs.append(souvenirObject);
		else
			return false;
	}

	if (!stadiumGraph.LoadFromJson(graphJsonArray))
		return false;

	return true;
}

bool Settings::SaveStadiums()
{
	QDir saveDir(dataFilePath);

	if (!saveDir.exists())
		saveDir.mkpath(dataFilePath);

	QFile saveFile(dataFile);

	if (!saveFile.open(QIODevice::WriteOnly))
		return false;

	QJsonObject jsonDoc;
	QJsonArray  stadiumJsonArray;
	QJsonArray  souvenirJsonArray;
	QJsonArray  graphJsonArray;

	for (auto &stadium : stadiums)
		stadiumJsonArray.append(stadium.SaveToJson());

	for (auto &souvenir : souvenirs)
		souvenirJsonArray.append(souvenir.SaveToJson());

	graphJsonArray = stadiumGraph.SaveToJson();

	jsonDoc["Graph"]     = graphJsonArray;
	jsonDoc["Stadiums"]  = stadiumJsonArray;
	jsonDoc["Souvenirs"] = souvenirJsonArray;

	saveFile.write(QJsonDocument(jsonDoc).toJson());

	return true;
}