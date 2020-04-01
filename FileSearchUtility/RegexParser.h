#pragma once

#include <QObject>

class RegexParser : public QObject
{
	Q_OBJECT
public:
	RegexParser();
	~RegexParser();

private:

public slots:
	void run();

	void validateRegexp(const );
	void 

signals:
	void workFinished();
	void regexpValidated(const bool& res);
};