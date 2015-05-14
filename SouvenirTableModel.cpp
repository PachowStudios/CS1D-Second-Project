#include "SouvenirTableModel.h"

SouvenirTableModel::SouvenirTableModel(QObject *parent)
	: QAbstractTableModel(parent)
{ }

void SouvenirTableModel::ShowSouvenirs(SouvenirList &souvenirs)
{
	layoutAboutToBeChanged();
	this->souvenirs = &souvenirs;
	layoutChanged();
}

int SouvenirTableModel::rowCount(const QModelIndex &parent) const
{
	if (!souvenirs)
		return 0;

	return souvenirs->count();
}

int SouvenirTableModel::columnCount(const QModelIndex &parent) const
{
	return Columns::NumColumns;
}

QVariant SouvenirTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
			case Name:  return "Name";
			case Price: return "Price";
		}
	}

	return QVariant();
}

QVariant SouvenirTableModel::data(const QModelIndex &index, int role) const
{
	if (!souvenirs)
		return QVariant();

	if (index.isValid() && role == Qt::DisplayRole)
	{
		Souvenir &souvenir = (*souvenirs)[index.row()];

		switch (index.column())
		{
			case Name:  return souvenir.name;
			case Price: return QLocale().toCurrencyString(souvenir.price);
		}
	}

	return QVariant();
}

bool SouvenirTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!souvenirs)
		return false;

	if (index.isValid() && role == Qt::EditRole)
	{
		Souvenir &souvenir = (*souvenirs)[index.row()];

		switch (index.column())
		{
			case Name:  
				souvenir.name = value.toString();
				break;
			case Price:
				souvenir.price = QLocale().toDouble(value.toString());
				break;
		}

		return true;
	}

	return false;
}

Qt::ItemFlags SouvenirTableModel::flags(const QModelIndex &index) const
{
	if (index.isValid())
		return Qt::ItemFlag::ItemIsEnabled 
		     | Qt::ItemFlag::ItemIsSelectable 
			 | Qt::ItemFlag::ItemIsEditable;
	else
		return Qt::ItemFlag::NoItemFlags;
}