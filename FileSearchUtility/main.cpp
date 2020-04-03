#include "FileSearchUtility.h"
#include <QtWidgets/QApplication>
#include <QThread>
#include <QTranslator>
#include "FileSearcher.h"
#include "RegexParser.h"

#define THREAD_WAIT_TIME 100

void connect(QPointer<FileSearcher>& fileSearcher, QPointer<RegexParser>& regexParser, QPointer<FileSearchUtility>& window)
{
	// view -> regexp parser
	QObject::connect(window, &FileSearchUtility::validateRegexp, regexParser, &RegexParser::validateRegexp);

	// regexp parser -> view
	QObject::connect(regexParser, &RegexParser::regexpValidated, window, &FileSearchUtility::regexpValidated);
	QObject::connect(regexParser, &RegexParser::setStatus, window, &FileSearchUtility::setStatus);

	// view -> file searcher
	QObject::connect(window, &FileSearchUtility::searchForFiles, fileSearcher, &FileSearcher::searchForFiles);
	QObject::connect(window, &FileSearchUtility::stopSearch, fileSearcher, &FileSearcher::stopSearch);
	
	// file searcher -> view
	QObject::connect(fileSearcher, &FileSearcher::setStatus, window, &FileSearchUtility::setStatus);
	QObject::connect(fileSearcher, &FileSearcher::haveSomeFile, window, &FileSearchUtility::haveSomeFile);
	QObject::connect(fileSearcher, &FileSearcher::searchFinished, window, &FileSearchUtility::searchFinished);
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

	QTranslator translator;
	if (translator.load("FileSearchUtility_" + QLocale::system().name()))
		a.installTranslator(&translator);

	QPointer<FileSearchUtility> w = new FileSearchUtility();
	qRegisterMetaType<RegexpValidateData>("RegexpValidateData");

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

		connect(fileSearcher, regexParser, w);

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
