#include "Souvenir.h"

Souvenir::Souvenir(QString name, double price)
	: name(name), price(price)
{ }

bool Souvenir::LoadFromJson(const QJsonObject &json)
{
	if (json.contains("Name") &&
		json.contains("Price"))
	{
		name  = json["Name"].toString();
		price = json["Price"].toDouble();
	}
	else
		return false;

	return true;
}

QJsonObject Souvenir::SaveToJson() const
{
	QJsonObject json;

	json["Name"]  = name;
	json["Price"] = price;

	return json;
}