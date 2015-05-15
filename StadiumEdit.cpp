#include "StadiumEdit.h"

StadiumEdit::StadiumEdit(QWidget *parent)
	: QDialog(parent)
{ 
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	stadiumTableModel = new StadiumTableModel();
	stadiumTableModel->ShowStadiums(AppSettings.stadiums);

	ui.stadiumTable->setModel(stadiumTableModel);

	connect(ui.addButton,    SIGNAL(clicked()),
			this,            SLOT(AddStadium()));
	connect(ui.removeButton, SIGNAL(clicked()),
			this,            SLOT(RemoveStadium()));
	connect(ui.saveButton,   SIGNAL(clicked()),
			this,            SLOT(Save()));
}

void StadiumEdit::AddStadium()
{
	Stadium *newStadium = new Stadium();
	newStadium->name = "New Stadium";
	stadiumTableModel->AddStadium(*newStadium);
}

void StadiumEdit::RemoveStadium()
{
	QModelIndex index = ui.stadiumTable->selectionModel()->currentIndex();

	if (index.isValid())
	{
		AppSettings.stadiumGraph.RemoveNode(AppSettings.stadiums[index.row()].ID);
		stadiumTableModel->RemoveStadium(index.row());
	}
}

void StadiumEdit::Save()
{
	AppSettings.SaveStadiums();
	accept();
}