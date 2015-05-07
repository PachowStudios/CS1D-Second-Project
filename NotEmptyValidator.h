#ifndef NOTEMPTYVALIDATOR_H
#define NOTEMPTYVALIDATOR_H

#include <QValidator>
#include <QLineEdit>
#include <QVariant>

class NotEmptyValidator : public QValidator
{
	Q_OBJECT

public:
	NotEmptyValidator(QObject *parent = 0);

	State validate(QString &input, int &pos) const;
};

#endif