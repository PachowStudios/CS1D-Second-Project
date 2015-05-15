#include "Souvenir.h"

Souvenir::Souvenir(QString name, double price)
	: name(name), price(price)
{ }

double Souvenir::CalculateTotalPrice(const QList<Souvenir> &souvenirs)
{
	double price = 0.0;

	for (auto &souvenir : souvenirs)
		price += souvenir.price;

	return price;
}

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