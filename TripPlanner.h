#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include "ui_TripPlanner.h"
#include "StadiumListModel.h"
#include "CurrentTrip.h"
#include "Settings.h"

#include <QDialog>
#include <QMessageBox>

class TripPlanner : public QDialog
{
	Q_OBJECT

public:
	TripPlanner(QWidget *parent = 0);

private:
	Ui::TripPlanner ui;

	Stadium     angelStadium;
	StadiumList availableStadiums;

	StadiumListModel *availableStadiumsModel = nullptr;

	private slots:
	void StartTrip();
};

#endif