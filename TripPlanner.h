#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include "ui_TripPlanner.h"
#include "StadiumListModel.h"
#include "Settings.h"

#include <QDialog>

class TripPlanner : public QDialog
{
	Q_OBJECT

public:
	TripPlanner(QWidget *parent = 0);

private:
	Ui::TripPlanner ui;

	StadiumList availableStadiums;
	StadiumList chosenStadiums;

	StadiumListModel *availableStadiumsModel = nullptr;
	StadiumListModel *chosenStadiumsModel = nullptr;

	private slots:
	void AddStadium();
	void RemoveStadium();
};

#endif