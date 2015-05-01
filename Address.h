#ifndef ADDRESS_H
#define ADDRESS_H

#include <QVariant>
#include <QJsonObject>

class Address
{
public:
	Address() = default;
	Address(QString street, QString city, QString state, int zipCode);

	bool        LoadFromJson(const QJsonObject &json);
	QJsonObject SaveToJson() const;
	
	QString street = "";
	QString city = "";
	QString state = "";
	int     zipCode = 0;
};

#endif