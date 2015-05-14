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
	void AddStadium(Stadium &stadium);
	void RemoveStadium(int row);

	int      rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
	StadiumList *stadiums = nullptr;
};

#endif