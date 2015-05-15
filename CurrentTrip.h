#ifndef CURRENTTRIP_H
#define CURRENTTRIP_H

#include "ui_CurrentTrip.h"
#include "StadiumListModel.h"
#include "SouvenirTableModel.h"
#include "Stadium.h"
#include "Souvenir.h"
#include "Settings.h"

#include <QDialog>
#include <QLocale>

class CurrentTrip : public QDialog
{
	Q_OBJECT

public:
	CurrentTrip(StadiumList trip, QWidget *parent = 0);

private:
	void SetCurrentStadium(const Stadium &stadium);
	void SetLegDistance(double distance);
	void SetTotalDistance(double distance);
	void SetGrandTotal(double price);

	Ui::CurrentTrip ui;

	StadiumList trip;
	int         currentStadiumIndex = 0;
	int         totalDistance = 0;

	StadiumList  legStadiumsVisited;
	StadiumList  tripStadiumsVisited;
	SouvenirList availableSouvenirs;
	SouvenirList purchasedSouvenirs;

	StadiumListModel   *legStadiumsVisitedModel = nullptr;
	StadiumListModel   *tripStadiumsVisitedModel = nullptr;
	SouvenirTableModel *availableSouvenirsModel = nullptr;
	SouvenirTableModel *purchasedSouvenirsModel = nullptr;

	private slots:
	void PurchaseSouvenir();
	void GoToNextStadium();
};

#endif