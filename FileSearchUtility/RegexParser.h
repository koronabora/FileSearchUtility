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

signals:
	void workFinished();
};