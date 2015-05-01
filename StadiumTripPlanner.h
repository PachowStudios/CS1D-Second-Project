#ifndef STADIUMTRIPPLANNER_H
#define STADIUMTRIPPLANNER_H

#include "ui_StadiumTripPlanner.h"

#include <QMainWindow>

class StadiumTripPlanner : public QMainWindow
{
	Q_OBJECT

public:
	StadiumTripPlanner(QWidget *parent = 0);
	~StadiumTripPlanner();

private:
	Ui::StadiumTripPlanner ui;
};

#endif
