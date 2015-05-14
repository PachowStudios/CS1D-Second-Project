#ifndef CURRENTTRIP_H
#define CURRENTTRIP_H

#include "ui_CurrentTrip.h"
#include "SouvenirTableModel.h"
#include "Stadium.h"
#include "Souvenir.h"
#include "Settings.h"

#include <QDialog>

class CurrentTrip : public QDialog
{
	Q_OBJECT

public:
	CurrentTrip(StadiumList trip, QWidget *parent = 0);

private:
	Ui::CurrentTrip ui;

	StadiumList trip;
};

#endif