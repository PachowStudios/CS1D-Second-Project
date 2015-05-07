#include "Stadium.h"

Stadium::Stadium(QString name, QString team, int phoneNumber, int capacity, Address address, Date dateOpened)
	: name(name), team(team), phoneNumber(phoneNumber), capacity(capacity), address(address), dateOpened(dateOpened)
{ }

bool Stadium::LoadFromJson(const QJsonObject &json)
{
	if (json.contains("Name")        &&
		json.contains("Team")        &&
		json.contains("PhoneNumber") &&
		json.contains("Capacity")    &&
		json.contains("Address")     &&
		json.contains("DateOpened"))
	{
		name        = json["Name"].toString();
		team        = json["Team"].toString();
		phoneNumber = json["PhoneNumber"].toInt();
		capacity    = json["Capacity"].toInt();
	}
	else
		return false;

	if (!address.LoadFromJson(json["Address"].toObject()) ||
		!dateOpened.LoadFromJson(json["DateOpened"].toObject()))
		return false;

	return true;
}

QJsonObject Stadium::SaveToJson() const
{
	QJsonObject json;

	json["Name"]        = name;
	json["Team"]        = team;
	json["PhoneNumber"] = phoneNumber;
	json["Capacity"]    = capacity;
	json["Address"]     = address.SaveToJson();
	json["DateOpened"]  = dateOpened.SaveToJson();

	return json;
}