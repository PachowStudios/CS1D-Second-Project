#include "FieldsMatchValidator.h"

FieldsMatchValidator::FieldsMatchValidator(const QLineEdit &otherField, QObject *parent)
	: otherField(&otherField), QValidator(parent)
{ }

QValidator::State FieldsMatchValidator::validate(QString &input, int &pos) const
{
	if (input == otherField->text() &&
		input != "")
		return State::Acceptable;
	else
		return State::Intermediate;
}