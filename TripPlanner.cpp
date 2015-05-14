#include "TripPlanner.h"

TripPlanner::TripPlanner(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	availableStadiums = StadiumList(AppSettings.stadiums);
	availableStadiumsModel = new StadiumListModel();
	availableStadiumsModel->ShowStadiums(availableStadiums);
	ui.availableStadiums->setModel(availableStadiumsModel);

	chosenStadiumsModel = new StadiumListModel();
	chosenStadiumsModel->ShowStadiums(chosenStadiums);
	ui.chosenStadiums->setModel(chosenStadiumsModel);

	connect(ui.addButton,    SIGNAL(clicked()),
			this,            SLOT(AddStadium()));
	connect(ui.removeButton, SIGNAL(clicked()),
			this,            SLOT(RemoveStadium()));
}

void TripPlanner::AddStadium()
{
	QModelIndex index = ui.availableStadiums->selectionModel()->currentIndex();

	if (index.isValid())
	{
		chosenStadiumsModel->AddStadium(availableStadiums[index.row()]);
		availableStadiumsModel->RemoveStadium(index.row());
	}
}

void TripPlanner::RemoveStadium()
{
	QModelIndex index = ui.chosenStadiums->selectionModel()->currentIndex();

	if (index.isValid())
	{
		availableStadiumsModel->AddStadium(chosenStadiums[index.row()]);
		chosenStadiumsModel->RemoveStadium(index.row());
	}
}