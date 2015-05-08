#include "Stadium.h"

Stadium::Stadium(QString name, QString team, int phoneNumber, int capacity, Address address, Date dateOpened)
	: name(name), team(team), phoneNumber(phoneNumber), capacity(capacity), address(address), dateOpened(dateOpened)
{ }

bool Stadium::LoadFromJson(const QJsonObject &json)
{
	if (json.contains("Name")        &&
		json.contains("Team")        &&
		json.contains("League")      &&
		json.contains("Grass")       &&
		json.contains("Capacity")    &&
		json.contains("PhoneNumber") &&
		json.contains("DateOpened")  &&
		json.contains("Address"))
	{
		name        = json["Name"].toString();
		team        = json["Team"].toString();
		league      = StringToLeague(json["League"].toString());
		grass       = json["Grass"].toBool();
		capacity    = json["Capacity"].toInt();
		phoneNumber = json["PhoneNumber"].toInt();
	}
	else
		return false;

	if (!dateOpened.LoadFromJson(json["DateOpened"].toObject()) ||
		!address.LoadFromJson(json["Address"].toObject()))
		return false;

	return true;
}

QJsonObject Stadium::SaveToJson() const
{
	QJsonObject json;

	json["Name"]        = name;
	json["Team"]        = team;
	json["League"]      = LeagueToString(league);
	json["Grass"]       = grass;
	json["Capacity"]    = capacity;
	json["PhoneNumber"] = phoneNumber;
	json["DateOpened"]  = dateOpened.SaveToJson();
	json["Address"]     = address.SaveToJson();

	return json;
}

Stadium::League Stadium::StringToLeague(QString league)
{
	if (league == "American")
		return American;
	else if (league == "National")
		return National;
	else
		return American;
}

QString Stadium::LeagueToString(Stadium::League league)
{
	switch (league)
	{
		case American: return "American";
		case National: return "National";
		default:       return "Invalid League";
	}
}