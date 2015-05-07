#include "NotEmptyValidator.h"

NotEmptyValidator::NotEmptyValidator(QObject *parent)
	: QValidator(parent)
{ }

QValidator::State NotEmptyValidator::validate(QString &input, int &pos) const
{
	if (input != "")
		return State::Acceptable;
	else
		return State::Intermediate;
}