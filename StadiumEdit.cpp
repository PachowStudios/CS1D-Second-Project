#include "StadiumEdit.h"

StadiumEdit::StadiumEdit(QWidget *parent)
	: QDialog(parent)
{ 
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	stadiumTableModel = new StadiumTableModel();
	stadiumTableModel->ShowStadiums(AppSettings.stadiums);

	ui.stadiumTable->setModel(stadiumTableModel);

	connect(ui.buttons, SIGNAL(accepted()),
			this,       SLOT(Save()));
}

void StadiumEdit::Save()
{
	AppSettings.SaveStadiums();
	accept();
}