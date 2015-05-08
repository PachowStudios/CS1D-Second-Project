#ifndef STADIUMLISTMODEL_H
#define STADIUMLISTMODEL_H

#include "Stadium.h"

#include <QAbstractListModel>

class StadiumListModel : public QAbstractListModel
{
	Q_OBJECT

public:
	StadiumListModel(QObject *parent = 0);

	void ShowStadiums(StadiumList &stadiums);

	int           rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant      data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
	StadiumList *stadiums = nullptr;

signals:
	void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
};

#endif