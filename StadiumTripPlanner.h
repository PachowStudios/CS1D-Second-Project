#ifndef STADIUMTRIPPLANNER_H
#define STADIUMTRIPPLANNER_H

#include "ui_StadiumTripPlanner.h"
#include "StadiumView.h"
#include "TripPlanner.h"
#include "CustomTripPlanner.h"
#include "AdminLogin.h"
#include "StadiumEdit.h"
#include "SouvenirEdit.h"

#include <QMainWindow>
#include <QMessageBox>

class StadiumTripPlanner : public QMainWindow
{
	Q_OBJECT

public:
	StadiumTripPlanner(QWidget *parent = 0);
	~StadiumTripPlanner();

private:
	void SetAdminOptionsEnabled(bool enabled);

	Ui::StadiumTripPlanner ui;

	bool loggedIn = false;

	private slots:
	void ViewStadiums() const;
	void PlanTrip() const;
	void PlanCustomTrip() const;
	void CalculateMST() const;
	void LoginLogout();
	void EditStadiums() const;
	void EditSouvenirs() const;
};

#endif
