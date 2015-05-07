#include "AdminLogin.h"

AdminLogin::AdminLogin(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	disconnect(ui.buttons, SIGNAL(accepted()),
			   this,       SLOT(accept()));

	connect(ui.usernameBox, SIGNAL(textChanged(const QString&)),
			this,           SLOT(ValidateFields()));
	connect(ui.passwordBox, SIGNAL(textChanged(const QString&)),
			this,           SLOT(ValidateFields()));
	connect(ui.buttons,     SIGNAL(accepted()),
			this,           SLOT(Login()));
	connect(ui.buttons,     SIGNAL(rejected()),
			this,           SLOT(reject()));

	ui.usernameBox->setValidator(new NotEmptyValidator);
	ui.passwordBox->setValidator(new NotEmptyValidator);
	ValidateFields();

	ui.usernameBox->setFocus();
}

void AdminLogin::ValidateFields()
{
	bool valid = ui.usernameBox->hasAcceptableInput() &&
		         ui.passwordBox->hasAcceptableInput();

	ui.buttons->button(QDialogButtonBox::Ok)->setEnabled(valid);
}

void AdminLogin::Login()
{
	if (AppSettings.adminLogin.Authenticate(ui.usernameBox->text(), ui.passwordBox->text()))
		this->accept();
	else
	{
		(new QMessageBox(QMessageBox::Critical,
			             "", "Invalid username or password.\nPlease try again."))->exec();

		ui.usernameBox->clear();
		ui.passwordBox->clear();
		ui.usernameBox->setFocus();
	}
}