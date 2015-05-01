#include "Date.h"

Date::Date(int month, int day, int year)
	: month(month), day(day), year(year)
{ }

bool Date::LoadFromJson(const QJsonObject &json)
{
	if (json.contains("Month") &&
		json.contains("Day")   &&
		json.contains("Year"))
	{
		month = json["Month"].toInt();
		day   = json["Day"].toInt();
		year  = json["Year"].toInt();
	}
	else
	{
		return false;
	}

	return true;
}

QJsonObject Date::SaveToJson() const
{
	QJsonObject json;

	json["Month"] = month;
	json["Day"]   = day;
	json["Year"]  = year;

	return json;
}

QString Date::ToString() const
{
	return MonthToString(month) + " " + day + ", " + year;
}

QString Date::MonthToString(int month)
{
	switch (month)
	{
		case 1:  return "January";
		case 2:  return "February";
		case 3:  return "March";
		case 4:  return "April";
		case 5:  return "May";
		case 6:  return "June";
		case 7:  return "July";
		case 8:  return "August";
		case 9:  return "September";
		case 10: return "October";
		case 11: return "November";
		case 12: return "December";
		default: return "Invalid Month";
	}
}

int Date::MonthToInt(QString month)
{
	if (month == "January")
		return 1;
	else if (month == "February")
		return 2;
	else if (month == "March")
		return 3;
	else if (month == "April")
		return 4;
	else if (month == "May")
		return 5;
	else if (month == "June")
		return 6;
	else if (month == "July")
		return 7;
	else if (month == "August")
		return 8;
	else if (month == "September")
		return 9;
	else if (month == "October")
		return 10;
	else if (month == "November")
		return 11;
	else if (month == "December")
		return 12;
	else
		return 0;
}