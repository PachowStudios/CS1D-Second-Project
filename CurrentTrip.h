#ifndef CURRENTTRIP_H
#define CURRENTTRIP_H

#include "ui_CurrentTrip.h"

#include <QDialog>

class CurrentTrip : public QDialog
{
	Q_OBJECT

public:
	CurrentTrip(QWidget *parent = 0);


private:
	Ui::CurrentTrip ui;
};

#endif