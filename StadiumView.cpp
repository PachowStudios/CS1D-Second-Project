#include "StadiumView.h"

StadiumView::StadiumView(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	stadiumTableModel = new StadiumTableModel();
	stadiumTableModel->ShowStadiums(AppSettings.stadiums);

	ui.stadiumTable->setModel(stadiumTableModel);
	ui.stadiumTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

	connect(ui.buttons, SIGNAL(rejected()),
			this,       SLOT(reject()));
}