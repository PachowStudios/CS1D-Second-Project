#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include "ui_AdminLogin.h"
#include "NotEmptyValidator.h"
#include "Settings.h"

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>

class AdminLogin : public QDialog
{
	Q_OBJECT

public:
	AdminLogin(QWidget *parent = 0);

private:
	Ui::AdminLogin ui;

	private slots:
	void ValidateFields();
	void Login();
};

#endif