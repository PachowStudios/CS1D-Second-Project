#ifndef LOADSTADIUMFILE_H
#define LOADSTADIUMFILE_H

#include "ui_LoadStadiumFile.h"
#include "FileValidator.h"
#include "Settings.h"

#include <QDialog>
#include <QPushButton>
#include <QFileDialog>
#include <QCloseEvent>
#include <QKeyEvent>

class LoadStadiumFile : public QDialog
{
	Q_OBJECT

public:
	LoadStadiumFile(QWidget *parent = 0);

private:
	void closeEvent(QCloseEvent *event);
	void keyPressEvent(QKeyEvent *event);

	Ui::LoadStadiumFile ui;

	private slots:
	void ValidateFields();
	void SelectFile();
	void Apply();
};

#endif