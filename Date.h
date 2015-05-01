#ifndef DATE_H
#define DATE_H

#include <QVariant>
#include <QJsonObject>

class Date
{
public:
	Date() = default;
	Date(int month, int day, int year);

	bool        LoadFromJson(const QJsonObject &json);
	QJsonObject SaveToJson() const;
	QString     ToString() const;

	static QString MonthToString(int month);
	static int     MonthToInt(QString month);

	int month = 0;
	int day = 0;
	int year = 0;
};

#endif