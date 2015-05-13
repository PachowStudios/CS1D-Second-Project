#include "StadiumTripPlanner.h"

StadiumTripPlanner::StadiumTripPlanner(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.viewStadiumsButton,     SIGNAL(clicked()),
			this,                      SLOT(ViewStadiums()));
	connect(ui.adminMenuLoginLogout,   SIGNAL(triggered()),
			this,                      SLOT(LoginLogout()));
	connect(ui.adminMenuEditSouvenirs, SIGNAL(triggered()),
			this,                      SLOT(EditSouvenirs()));
	connect(ui.dialogButtons,          SIGNAL(rejected()),
			this,                      SLOT(close()));
}

StadiumTripPlanner::~StadiumTripPlanner()
{ }

void StadiumTripPlanner::SetAdminOptionsEnabled(bool enabled)
{
	ui.adminMenuEditSouvenirs->setEnabled(enabled);
}

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

	SetAdminOptionsEnabled(loggedIn);
}

void StadiumTripPlanner::EditSouvenirs() const
{
	if (!loggedIn)
		return;

	(new SouvenirEdit)->exec();
}
