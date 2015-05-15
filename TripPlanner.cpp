#include "TripPlanner.h"

TripPlanner::TripPlanner(QWidget *parent)
	: QDialog(parent)
{ 
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	availableStadiums = StadiumList(AppSettings.stadiums);
	angelStadium = AppSettings.GetStadium(Settings::SearchBy::ID, QString::number(1));
	availableStadiums.removeAt(0);

	availableStadiumsModel = new StadiumListModel();
	availableStadiumsModel->ShowStadiums(availableStadiums);
	ui.availableStadiums->setModel(availableStadiumsModel);

	disconnect(ui.buttons, SIGNAL(accepted()),
			   this,       SLOT(accept()));

	connect(ui.buttons, SIGNAL(accepted()),
			this,       SLOT(StartTrip()));
	connect(ui.buttons, SIGNAL(rejected()),
			this,       SLOT(reject()));
}

void TripPlanner::StartTrip()
{
	QModelIndex index = ui.availableStadiums->selectionModel()->currentIndex();

	if (!index.isValid())
	{
		(new QMessageBox(QMessageBox::Critical,
			             "", "You must select a stadium to visit!"))->exec();
		return;
	}
	else
	{
		StadiumList trip;
		trip.append(angelStadium);
		trip.append(availableStadiums[index.row()]);

		close();
		(new CurrentTrip(trip))->exec();
	}
}