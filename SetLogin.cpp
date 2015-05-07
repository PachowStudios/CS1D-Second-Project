#include "SetLogin.h"

SetLogin::SetLogin(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.usernameBox,        SIGNAL(textChanged(const QString&)),
			this,                  SLOT(ValidateFields()));
	connect(ui.passwordBox,        SIGNAL(textChanged(const QString&)),
			this,                  SLOT(ValidateFields()));
	connect(ui.confirmPasswordBox, SIGNAL(textChanged(const QString&)),
			this,                  SLOT(ValidateFields()));
	connect(ui.buttons,            SIGNAL(accepted()),
			this,                  SLOT(Apply()));
	connect(ui.buttons,            SIGNAL(rejected()),
			this,                  SLOT(reject()));

	ui.usernameBox->setValidator(new NotEmptyValidator);
	ui.passwordBox->setValidator(new NotEmptyValidator);
	ui.confirmPasswordBox->setValidator(new FieldsMatchValidator(*ui.passwordBox));
	ValidateFields();

	ui.usernameBox->setFocus();
}

void SetLogin::closeEvent(QCloseEvent *event)
{
	this->reject();
}

void SetLogin::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
		this->reject();
	else
		QDialog::keyPressEvent(event);
}

void SetLogin::ValidateFields()
{
	bool valid = ui.usernameBox->hasAcceptableInput() &&
		         ui.passwordBox->hasAcceptableInput() &&
		         ui.confirmPasswordBox->hasAcceptableInput();

	ui.buttons->button(QDialogButtonBox::Ok)->setEnabled(valid);
}

void SetLogin::Apply()
{
	AppSettings.adminLogin.SetUsername(ui.usernameBox->text());
	AppSettings.adminLogin.SetPassword(ui.passwordBox->text());
	AppSettings.SaveCredentials();
	this->accept();
}