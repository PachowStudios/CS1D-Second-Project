#ifndef STADIUM_H
#define STADIUM_H

#include "Address.h"
#include "Date.h"

#include <QVariant>
#include <QJsonObject>

class Stadium
{
public:
	Stadium() = default;
	Stadium(QString name, QString team, int phoneNumber, int capacity, Address address, Date dateOpened);

	bool        LoadFromJson(const QJsonObject &json, bool allowPartial = false);
	QJsonObject SaveToJson() const;
	
	QString name = "";
	QString team = "";
	int     phoneNumber = 0;
	int     capacity = 0;
	Address address;
	Date    dateOpened;
};

#endif