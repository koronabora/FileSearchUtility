#pragma once

#include <QObject>
#include <QThread>
#include "Structs.h"

class RegexParser : public QObject
{
	Q_OBJECT
public:
	RegexParser();
	~RegexParser();

private:
	bool parse(const QString& data);

public slots:
	void run();
	void validateRegexp(RegexpValidateData data);

signals:
	void workFinished();
	void regexpValidated(RegexpValidateData data);
	void setStatus(const QString& text);
};