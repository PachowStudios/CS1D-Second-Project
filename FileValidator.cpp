#include "FileValidator.h"

FileValidator::FileValidator(QString extension, QObject *parent)
	: extension(extension), QValidator(parent)
{ }

QValidator::State FileValidator::validate(QString &input, int &pos) const
{
	QFileInfo fileInfo(input);

	if (fileInfo.exists()     && 
		fileInfo.isReadable() &&
		fileInfo.completeSuffix() == extension)
		return State::Acceptable;
	else
		return State::Intermediate;

}