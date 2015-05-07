#ifndef FIELDSMATCHVALIDATOR_H
#define FIELDSMATCHVALIDATOR_H

#include <QValidator>
#include <QLineEdit>
#include <QString>

class FieldsMatchValidator : public QValidator
{
	Q_OBJECT

public:
	FieldsMatchValidator(const QLineEdit &otherField, QObject *parent = 0);

	State validate(QString &input, int &pos) const;

private:
	const QLineEdit *otherField;
};

#endif