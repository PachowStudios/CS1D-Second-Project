#include "Date.h"

bool Date::LoadFromJson(const QJsonObject &json)
{
	if (json.contains("Month") &&
		json.contains("Day")   &&
		json.contains("Year"))
	{
		int year  = json["Year"].toInt();
		int month = json["Month"].toInt();
		int day   = json["Day"].toInt();
		setDate(year, month, day);
	}
	else
		return false;

	return true;
}

QJsonObject Date::SaveToJson() const
{
	QJsonObject json;

	json["Month"] = month();
	json["Day"]   = day();
	json["Year"]  = year();

	return json;
}