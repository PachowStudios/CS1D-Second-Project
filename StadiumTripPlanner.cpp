#include "StadiumTripPlanner.h"

StadiumTripPlanner::StadiumTripPlanner(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.dialogButtons, SIGNAL(rejected()),
			this,             SLOT(close()));
}

StadiumTripPlanner::~StadiumTripPlanner()
{ }
