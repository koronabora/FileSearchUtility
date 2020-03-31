#pragma once

#include <QObject>

class FileSearcher : public QObject
{
	Q_OBJECT
public:
	FileSearcher();
	~FileSearcher();

private:

public slots:
	void run();

signals:
	void workFinished();
};