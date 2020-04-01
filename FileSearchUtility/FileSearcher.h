#pragma once

#include <QObject>
#include "Structs.h"

class FileSearcher : public QObject
{
	Q_OBJECT
public:
	FileSearcher();
	~FileSearcher();

private:
	bool continueSearch = false;

public slots:
	void run();
	void searchForFiles(const QString& path, const RegexpValidateData& regexp);
	void stopSearch();

signals:
	void workFinished();
	void setStatus(const QString& text);
	void haveSomeFile(const QString& path, const quint64& size);
	void searchFinished();
};