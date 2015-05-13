#include "SouvenirEdit.h"

SouvenirEdit::SouvenirEdit(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	souvenirTableModel = new SouvenirTableModel();
	souvenirTableModel->ShowSouvenirs(AppSettings.souvenirs);
	ui.souvenirTable->setModel(souvenirTableModel);

	connect(ui.buttons, SIGNAL(accepted()),
			this,       SLOT(Save()));

	ui.souvenirTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
}

void SouvenirEdit::Save()
{
	AppSettings.SaveStadiums();
	this->accept();
}