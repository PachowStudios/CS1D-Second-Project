#ifndef STADIUMTRIPPLANNER_H
#define STADIUMTRIPPLANNER_H

#include <QtWidgets/QMainWindow>
#include "ui_StadiumTripPlanner.h"

class StadiumTripPlanner : public QMainWindow
{
	Q_OBJECT

public:
	StadiumTripPlanner(QWidget *parent = 0);
	~StadiumTripPlanner();

private:
	Ui::StadiumTripPlannerClass ui;
};

#endif // STADIUMTRIPPLANNER_H
