#include "FileSearchUtility.h"
#include <QtWidgets/QApplication>
#include <QThread>

#include "FileSearcher.h"
#include "RegexParser.h"

#define THREAD_WAIT_TIME 100

void connect(QPointer<FileSearcher>& fileSearcher, QPointer<RegexParser>& regexParser)
{

}

void stopThread(QPointer<QThread>& thread)
{
	if (thread)
	{
		thread->wait(THREAD_WAIT_TIME);
		if (thread->isRunning())
			thread->terminate();
		thread->deleteLater();
	}
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QPointer<FileSearchUtility> w = new FileSearchUtility();

	try {
		QPointer<QThread> fsThread = new QThread();
		QPointer<FileSearcher> fileSearcher = new FileSearcher();
		fileSearcher->moveToThread(fsThread);
		QObject::connect(fsThread, &QThread::started, fileSearcher, &FileSearcher::run);
		QObject::connect(fileSearcher, &FileSearcher::workFinished, fsThread, &QThread::terminate);
		fsThread->start();

		QPointer<QThread> rpThread = new QThread();
		QPointer<RegexParser> regexParser = new RegexParser();
		regexParser->moveToThread(rpThread);
		QObject::connect(rpThread, &QThread::started, regexParser, &RegexParser::run);
		QObject::connect(regexParser, &RegexParser::workFinished, rpThread, &QThread::terminate);
		rpThread->start();

		connect(fileSearcher, regexParser);

		w->show();
		int res = a.exec();

		fileSearcher->deleteLater();
		regexParser->deleteLater();

		stopThread(fsThread);
		stopThread(rpThread);

		w->deleteLater();

		return res;
	}
	catch (...)
	{
	}
	return -1;
}
