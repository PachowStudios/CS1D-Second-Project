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
			case Street:      return "Street";
			case City:        return "City";
			case State:       return "State";
			case ZipCode:     return "ZipCode";
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
			case Capacity:    return QLocale().toString(stadium.capacity);
			case DateOpened:  return stadium.dateOpened.toString("MMMM d, yyyy");
			case Street:      return stadium.address.street;
			case City:        return stadium.address.city;
			case State:       return stadium.address.state;
			case ZipCode:     return stadium.address.zipCode;
			case PhoneNumber: return stadium.phoneNumber;
		}
	}

	return QVariant();
}

bool StadiumTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!stadiums)
		return false;

	if (index.isValid() && role == Qt::EditRole)
	{
		Stadium &stadium = (*stadiums)[index.row()];

		switch (index.column())
		{
			case Name:
				stadium.name = value.toString();
				break;
			case Team:
				stadium.team = value.toString();
				break;
			case League:
				stadium.league = Stadium::StringToLeague(value.toString());
				break;
			case Grass:
				stadium.grass = value.toString().toLower() == "yes";
				break;
			case Capacity:
				stadium.capacity = value.toInt();
				break;
			case DateOpened:
				break;
			case Street:
				stadium.address.street = value.toString();
				break;
			case City:
				stadium.address.city = value.toString();
				break;
			case State:
				stadium.address.state = value.toString();
				break;
			case ZipCode:
				stadium.address.zipCode = value.toString();
				break;
			case PhoneNumber:
				stadium.phoneNumber = value.toString();
				break;
		}

		return true;
	}

	return false;
}

Qt::ItemFlags StadiumTableModel::flags(const QModelIndex &index) const
{
	if (index.isValid())
		return Qt::ItemFlag::ItemIsEnabled
		     | Qt::ItemFlag::ItemIsSelectable
		     | Qt::ItemFlag::ItemIsEditable;
	else
		return Qt::ItemFlag::NoItemFlags;
}