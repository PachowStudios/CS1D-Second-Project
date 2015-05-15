#ifndef SOUVENIRTABLEMODEL_H
#define SOUVENIRTABLEMODEL_H

#include "Souvenir.h"

#include <QAbstractTableModel>
#include <QLocale>

class SouvenirTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	SouvenirTableModel(QObject *parent = 0);

	void ShowSouvenirs(SouvenirList &souvenirs);
	void AddSouvenir(Souvenir &souvenir);
	void RemoveSouvenir(int row);

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
		Price,
		NumColumns
	};

	SouvenirList *souvenirs = nullptr;
};

#endif