#ifndef SOUVENIR_H
#define SOUVENIR_H

#include <QVariant>
#include <QList>
#include <QJsonObject>

class Souvenir
{
public:
	Souvenir() = default;
	Souvenir(QString name, double price);

	bool LoadFromJson(const QJsonObject &json);
	QJsonObject SaveToJson() const;

	QString name = "";
	double  price = 0.0;
};

typedef QList<Souvenir> SouvenirList;

#endif