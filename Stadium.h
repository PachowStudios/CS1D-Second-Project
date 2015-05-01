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
	Stadium(QString name, QString team, Address address, qlonglong phoneNumber, Date dateOpened);

	bool        LoadFromJson(const QJsonObject &json, bool allowPartial = false);
	QJsonObject SaveToJson() const;
	
	QString   name = "";
	QString   team = "";
	Address   address;
	qlonglong phoneNumber = 0;
	Date      dateOpened;
};

#endif