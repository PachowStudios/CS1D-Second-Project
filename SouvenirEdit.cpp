#include "SouvenirEdit.h"

SouvenirEdit::SouvenirEdit(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	souvenirTableModel = new SouvenirTableModel();
	souvenirTableModel->ShowSouvenirs(AppSettings.souvenirs);

	ui.souvenirTable->setModel(souvenirTableModel);
	ui.souvenirTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeMode::Stretch);
	ui.souvenirTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeMode::Fixed);

	connect(ui.buttons, SIGNAL(accepted()),
			this,       SLOT(Save()));
}

void SouvenirEdit::Save()
{
	AppSettings.SaveStadiums();
	this->accept();
}