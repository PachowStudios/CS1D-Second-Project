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

void StadiumListModel::AddStadium(Stadium &stadium)
{
	beginInsertRows(QModelIndex(), 0, 0);
	stadiums->append(stadium);
	endInsertRows();
}

void StadiumListModel::RemoveStadium(int row)
{
	beginRemoveRows(QModelIndex(), row, row);
	stadiums->removeAt(row);
	endRemoveRows();
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