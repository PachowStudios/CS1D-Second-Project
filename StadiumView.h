#ifndef STADIUMVIEW_H
#define STADIUMVIEW_H

#include "ui_StadiumView.h"
#include "StadiumTableModel.h"
#include "Settings.h"

#include <QDialog>

class StadiumView : public QDialog
{
	Q_OBJECT

public:
	StadiumView(QWidget *parent = 0);

private:
	Ui::StadiumView ui;

	StadiumTableModel *stadiumTableModel = nullptr;
};

#endif