#ifndef STADIUMEDIT_H
#define STADIUMEDIT_H

#include "ui_StadiumEdit.h"
#include "Settings.h"

#include <QDialog>

class StadiumEdit : public QDialog
{
	Q_OBJECT

public:
	StadiumEdit(QWidget *parent = 0);

private:
	Ui::StadiumEdit ui;
};

#endif