#pragma once

#include <QObject>
#include <QDirIterator>
#include <QPointer>
#include <QDebug>
#include <QCoreApplication>
#include <atomic>
#include <QStringList>
#include "Structs.h"

class FileSearcher : public QObject
{
	Q_OBJECT
public:
	FileSearcher();
	~FileSearcher();

private:
	std::atomic_bool continueSearch = false;

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