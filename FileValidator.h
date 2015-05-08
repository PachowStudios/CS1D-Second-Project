#ifndef FILEVALIDATOR_H
#define FILEVALIDATOR_H

#include <QValidator>
#include <QFileInfo>
#include <QString>

class FileValidator : public QValidator
{
	Q_OBJECT

public:
	FileValidator(QString extension, QObject *parent = 0);

	State validate(QString &input, int &pos) const;

private:
	QString extension;
};

#endif