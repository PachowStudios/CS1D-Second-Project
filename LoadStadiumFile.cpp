#include "LoadStadiumFile.h"

LoadStadiumFile::LoadStadiumFile(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.selectFileButton, SIGNAL(released()),
			this,                SLOT(SelectFile()));
	connect(ui.selectFileBox,    SIGNAL(textChanged(const QString&)),
			this,                SLOT(ValidateFields()));
	connect(ui.buttons,          SIGNAL(accepted()),
			this,                SLOT(Apply()));
	connect(ui.buttons,          SIGNAL(rejected()),
			this,                SLOT(reject()));

	ui.selectFileBox->setValidator(new FileValidator("json"));
	ValidateFields();
}

void LoadStadiumFile::closeEvent(QCloseEvent *event)
{
	this->reject();
}

void LoadStadiumFile::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
		this->reject();
	else
		QDialog::keyPressEvent(event);
}

void LoadStadiumFile::ValidateFields()
{
	bool valid = ui.selectFileBox->hasAcceptableInput();

	ui.buttons->button(QDialogButtonBox::Ok)->setEnabled(valid);
}

void LoadStadiumFile::SelectFile()
{
	QString stadiumFile = QFileDialog::getOpenFileName(this, "Select Stadium File", "",
													   "Stadium Files (*.json)");

	ui.selectFileBox->setText(stadiumFile);
	ui.buttons->setFocus();
}

void LoadStadiumFile::Apply()
{
	AppSettings.LoadStadiums(ui.selectFileBox->text());
	AppSettings.SaveStadiums();
	this->accept();
}