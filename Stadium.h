#ifndef STADIUM_H
#define STADIUM_H

#include "Address.h"
#include "Date.h"

#include <QVariant>
#include <QList>
#include <QJsonObject>

class Stadium
{
public:
	enum League
	{
		American,
		National
	};

	Stadium() = default;
	Stadium(QString name, QString team, int phoneNumber, int capacity, Address address, Date dateOpened);

	bool        LoadFromJson(const QJsonObject &json);
	QJsonObject SaveToJson() const;

	static League  StringToLeague(QString league);
	static QString LeagueToString(League league);
	
	QString name = "";
	QString team = "";
	League  league = American;
	bool    grass = false;
	int     capacity = 0;
	QString phoneNumber = "";
	Date    dateOpened;
	Address address;
};

typedef QList<Stadium> StadiumList;

#endif