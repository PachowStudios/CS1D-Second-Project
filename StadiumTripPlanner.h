#ifndef STADIUMTRIPPLANNER_H
#define STADIUMTRIPPLANNER_H

#include "ui_StadiumTripPlanner.h"
#include "StadiumView.h"
#include "AdminLogin.h"

#include <QMainWindow>
#include <QMessageBox>

class StadiumTripPlanner : public QMainWindow
{
	Q_OBJECT

public:
	StadiumTripPlanner(QWidget *parent = 0);
	~StadiumTripPlanner();

private:
	Ui::StadiumTripPlanner ui;

	bool loggedIn = false;

	private slots:
	void ViewStadiums() const;
	void LoginLogout();
};

#endif
