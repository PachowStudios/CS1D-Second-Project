#include "StadiumTripPlanner.h"

StadiumTripPlanner::StadiumTripPlanner(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.viewStadiumsButton,   SIGNAL(clicked()),
			this,                    SLOT(ViewStadiums()));
	connect(ui.adminMenuLoginLogout, SIGNAL(triggered()),
			this,                    SLOT(LoginLogout()));
	connect(ui.dialogButtons,        SIGNAL(rejected()),
			this,                    SLOT(close()));
}

StadiumTripPlanner::~StadiumTripPlanner()
{ }

void StadiumTripPlanner::ViewStadiums() const
{
	(new StadiumView)->exec();
}

void StadiumTripPlanner::LoginLogout()
{
	if (loggedIn)
	{
		loggedIn = false;
		ui.adminMenuLoginLogout->setText("Login");

		(new QMessageBox(QMessageBox::Information,
			"", "You have been logged out."))->exec();
	}
	else
	{
		if ((new AdminLogin)->exec() == QDialog::Accepted)
		{
			loggedIn = true;
			ui.adminMenuLoginLogout->setText("Logout");
		}
	}
}
