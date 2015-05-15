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

	connect(ui.addButton,    SIGNAL(clicked()),
			this,            SLOT(AddSouvenir()));
	connect(ui.removeButton, SIGNAL(clicked()),
			this,            SLOT(RemoveSouvenir()));
	connect(ui.saveButton,   SIGNAL(clicked()),
			this,            SLOT(Save()));
}

void SouvenirEdit::AddSouvenir()
{
	souvenirTableModel->AddSouvenir(Souvenir("New Souvenir", 0));
}

void SouvenirEdit::RemoveSouvenir()
{
	QModelIndex index = ui.souvenirTable->selectionModel()->currentIndex();

	if (index.isValid())
		souvenirTableModel->RemoveSouvenir(index.row());
}

void SouvenirEdit::Save()
{
	AppSettings.SaveStadiums();
	accept();
}