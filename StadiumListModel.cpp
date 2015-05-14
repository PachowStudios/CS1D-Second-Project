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
	if (!stadiums)
		return;

	beginInsertRows(QModelIndex(), 0, 0);
	stadiums->append(stadium);
	endInsertRows();
}

void StadiumListModel::RemoveStadium(int row)
{
	if (!stadiums)
		return;

	beginRemoveRows(QModelIndex(), row, row);
	stadiums->removeAt(row);
	endRemoveRows();
}

void StadiumListModel::MoveUp(int row)
{
	if (!stadiums || row <= 0)
		return;

	layoutAboutToBeChanged();
	stadiums->move(row, row - 1);
	layoutChanged();
}

void StadiumListModel::MoveDown(int row)
{
	if (!stadiums || row >= stadiums->count() - 1)
		return;

	layoutAboutToBeChanged();
	stadiums->move(row, row + 1);
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