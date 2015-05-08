#include "StadiumListModel.h"

StadiumListModel::StadiumListModel(QObject *parent)
	: QAbstractListModel(parent)
{ }

void StadiumListModel::ShowStadiums(StadiumList &stadiums)
{
	layoutAboutToBeChanged();
	this->stadiums = &stadiums;
	layoutChanged();
}

int StadiumListModel::rowCount(const QModelIndex &parent) const
{
	if (!stadiums)
		return 0;

	return stadiums->count();
}

QVariant StadiumListModel::data(const QModelIndex &index, int role) const
{
	if (!stadiums)
		return QVariant();

	if (role == Qt::DisplayRole)
		return (*stadiums)[index.row()].name;

	return QVariant();
}