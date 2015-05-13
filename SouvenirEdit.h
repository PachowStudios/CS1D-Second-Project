#ifndef SOUVENIREDIT_H
#define SOUVENIREDIT_H

#include "ui_SouvenirEdit.h"
#include "SouvenirTableModel.h"
#include "Settings.h"

#include <QDialog>

class SouvenirEdit : public QDialog
{
	Q_OBJECT

public:
	SouvenirEdit(QWidget *parent = 0);

private:
	Ui::SouvenirEdit ui;

	SouvenirTableModel *souvenirTableModel = nullptr;

	private slots:
	void Save();
};

#endif