#include "CurrentTrip.h"

CurrentTrip::CurrentTrip(StadiumList trip, QWidget *parent)
	: trip(trip), QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	legStadiumsVisitedModel = new StadiumListModel();
	legStadiumsVisitedModel->ShowStadiums(legStadiumsVisited);
	ui.legStadiumsVisited->setModel(legStadiumsVisitedModel);

	tripStadiumsVisitedModel = new StadiumListModel();
	tripStadiumsVisitedModel->ShowStadiums(tripStadiumsVisited);
	ui.tripStadiumsVisited->setModel(tripStadiumsVisitedModel);

	availableSouvenirs = SouvenirList(AppSettings.souvenirs);
	availableSouvenirsModel = new SouvenirTableModel();
	availableSouvenirsModel->ShowSouvenirs(availableSouvenirs);
	ui.availableSouvenirs->setModel(availableSouvenirsModel);
	ui.availableSouvenirs->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Stretch);
	ui.availableSouvenirs->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeMode::Fixed);

	purchasedSouvenirsModel = new SouvenirTableModel();
	purchasedSouvenirsModel->ShowSouvenirs(purchasedSouvenirs);
	ui.purchasedSouvenirs->setModel(purchasedSouvenirsModel);
	ui.purchasedSouvenirs->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Stretch);
	ui.purchasedSouvenirs->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeMode::Fixed);

	SetCurrentStadium(trip[currentStadiumIndex]);
	tripStadiumsVisitedModel->AddStadium(trip[currentStadiumIndex]);

	connect(ui.purchaseSouvenirButton, SIGNAL(clicked()),
			this,                      SLOT(PurchaseSouvenir()));
	connect(ui.nextButton,             SIGNAL(clicked()),
			this,                      SLOT(GoToNextStadium()));
	connect(ui.cancelButton,           SIGNAL(clicked()),
			this,                      SLOT(reject()));
}

void CurrentTrip::SetCurrentStadium(const Stadium &stadium)
{
	ui.currentStadiumLabel->setText("Current Stadium: " + stadium.name);
}

void CurrentTrip::SetGrandTotal(double price)
{
	ui.grandTotalLabel->setText("Grand Total: " + QLocale().toCurrencyString(price));
}

void CurrentTrip::SetLegDistance(double distance)
{
	ui.legDistanceLabel->setText("Leg Distance: " + QString::number(distance));
}

void CurrentTrip::SetTotalDistance(double distance)
{
	ui.totalDistanceLabel->setText("Total Distance: " + QString::number(distance));
}

void CurrentTrip::PurchaseSouvenir()
{
	QModelIndex index = ui.availableSouvenirs->selectionModel()->currentIndex();

	if (index.isValid())
	{
		purchasedSouvenirsModel->AddSouvenir(availableSouvenirs[index.row()]);
		SetGrandTotal(Souvenir::CalculateTotalPrice(purchasedSouvenirs));
	}
}

void CurrentTrip::GoToNextStadium()
{
	if (currentStadiumIndex >= trip.count() - 1)
		return;

	currentStadiumIndex++;

	Path nextPath = AppSettings.stadiumGraph.CalculatePath(trip[currentStadiumIndex - 1].ID,
														   trip[currentStadiumIndex].ID);
	int pathDistance = AppSettings.stadiumGraph.CalculateDistance(nextPath);
	legStadiumsVisited = AppSettings.PathToStadiums(nextPath);

	legStadiumsVisitedModel->ShowStadiums(legStadiumsVisited);
	tripStadiumsVisitedModel->AddStadium(trip[currentStadiumIndex]);

	totalDistance += pathDistance;
	SetLegDistance(pathDistance);
	SetTotalDistance(totalDistance);
	SetCurrentStadium(trip[currentStadiumIndex]);

	if (currentStadiumIndex >= trip.count() - 1)
	{
		ui.nextButton->setText("Finish Trip");
		disconnect(ui.nextButton, SIGNAL(clicked()),
				   this,          SLOT(GoToNextStadium()));
		connect(ui.nextButton, SIGNAL(clicked()),
				this,          SLOT(close()));
	}
}