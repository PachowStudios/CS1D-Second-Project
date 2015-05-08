#include "StadiumTableModel.h"

StadiumTableModel::StadiumTableModel(QObject *parent)
	: QAbstractTableModel(parent)
{ }

void StadiumTableModel::ShowStadiums(StadiumList &stadiums)
{
	layoutAboutToBeChanged();
	this->stadiums = &stadiums;
	layoutChanged();
}

int StadiumTableModel::rowCount(const QModelIndex &parent) const
{
	if (!stadiums)
		return 0;

	return stadiums->count();
}

int StadiumTableModel::columnCount(const QModelIndex &parent) const
{
	return Columns::NumColumns;
}

QVariant StadiumTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
			case Name:        return "Name";
			case Team:        return "Team";
			case League:      return "League";
			case Grass:       return "Grass";
			case Capacity:    return "Capacity";
			case DateOpened:  return "Date Opened";
			case Address:     return "Address";
			case PhoneNumber: return "Phone Number";
		}
	}

	return QVariant();
}

QVariant StadiumTableModel::data(const QModelIndex &index, int role) const
{
	if (!stadiums)
		return QVariant();

	if (index.isValid() && role == Qt::DisplayRole)
	{
		Stadium &stadium = (*stadiums)[index.row()];

		switch (index.column())
		{
			case Name:        return stadium.name;
			case Team:        return stadium.team;
			case League:      return Stadium::LeagueToString(stadium.league);
			case Grass:       return stadium.grass ? "Yes" : "No";
			case Capacity:    return stadium.capacity;
			case DateOpened:  return stadium.dateOpened.ToString();
			case Address:     return stadium.address.ToString();
			case PhoneNumber: return stadium.phoneNumber;
		}
	}

	return QVariant();
}