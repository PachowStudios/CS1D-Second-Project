#ifndef DATE_H
#define DATE_H

#include <QVariant>
#include <QDate>
#include <QJsonObject>

class Date : public QDate
{
public:
	Date() = default;

	bool        LoadFromJson(const QJsonObject &json);
	QJsonObject SaveToJson() const;
};

#endif