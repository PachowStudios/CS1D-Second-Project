#ifndef STADIUMTABLEMODEL_H
#define STADIUMTABLEMODEL_H

#include "Stadium.h"

#include <QAbstractTableModel>
#include <QLocale>

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
	bool          setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;

private:
	enum Columns
	{
		Name,
		Team,
		League,
		Grass,
		Capacity,
		DateOpened,
		Street,
		City,
		State,
		ZipCode,
		PhoneNumber,
		NumColumns
	};

	StadiumList *stadiums = nullptr;
};

#endif