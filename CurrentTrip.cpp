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

	connect(ui.purchaseSouvenirButton, SIGNAL(clicked()),
			this,                      SLOT(PurchaseSouvenir()));
	connect(ui.nextButton,             SIGNAL(clicked()),
			this,                      SLOT(NextStadium()));
	connect(ui.cancelButton,           SIGNAL(clicked()),
			this,                      SLOT(reject()));
}

void CurrentTrip::StartTrip()
{

}

void CurrentTrip::PurchaseSouvenir()
{
	QModelIndex index = ui.availableSouvenirs->selectionModel()->currentIndex();

	if (index.isValid())
	{
		purchasedSouvenirsModel->AddSouvenir(availableSouvenirs[index.row()]);
		ui.grandTotalLabel->setText("Grand Total: " + QLocale().toCurrencyString(Souvenir::CalculateTotalPrice(purchasedSouvenirs)));
	}
}

void CurrentTrip::NextStadium()
{

}