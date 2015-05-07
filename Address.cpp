#include "Address.h"

Address::Address(QString street, QString city, QString state, int zipCode)
	: street(street), city(city), state(state), zipCode(zipCode)
{ }

bool Address::LoadFromJson(const QJsonObject &json)
{
	if (json.contains("Street") &&
		json.contains("City")   &&
		json.contains("State")  &&
		json.contains("ZipCode"))
	{
		street  = json["Street"].toString();
		city    = json["City"].toString();
		state   = json["State"].toString();
		zipCode = json["ZipCode"].toInt();
	}
	else
		return false;

	return true;
}

QJsonObject Address::SaveToJson() const
{
	QJsonObject json;

	json["Street"]  = street;
	json["City"]    = city;
	json["State"]   = state;
	json["Zipcode"] = zipCode;

	return json;
}