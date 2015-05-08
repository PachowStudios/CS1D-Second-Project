#ifndef STADIUMTABLEMODEL_H
#define STADIUMTABLEMODEL_H

#include "Settings.h"
#include "Stadium.h"

#include <QAbstractTableModel>

class StadiumTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	StadiumTableModel(QObject *parent = 0);

	void ShowStadiums(StadiumList &stadiums);

	int           rowCount(const QModelIndex &parent = QModelIndex()) const;
	int           columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant      headerData(int section, Qt::Orientation orientation, int role) const;
	QVariant      data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
	enum Columns
	{
		Name,
		Team,
		League,
		Grass,
		Capacity,
		DateOpened,
		Address,
		PhoneNumber,
		NumColumns
	};

	StadiumList *stadiums = nullptr;
};

#endif