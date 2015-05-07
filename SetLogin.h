#ifndef SETLOGIN_H
#define SETLOGIN_H

#include "ui_SetLogin.h"
#include "NotEmptyValidator.h"
#include "FieldsMatchValidator.h"
#include "Settings.h"

#include <QDialog>
#include <QPushButton>
#include <QCloseEvent>
#include <QKeyEvent>

class SetLogin : public QDialog
{
	Q_OBJECT

public:
	SetLogin(QWidget *parent = 0);

private:
	void closeEvent(QCloseEvent *event);
	void keyPressEvent(QKeyEvent *event);

	Ui::SetLogin ui;

	private slots:
	void ValidateFields();
	void Apply();
};
#endif