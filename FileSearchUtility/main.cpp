#include "FileSearchUtility.h"
#include <QtWidgets/QApplication>
#include <QThread>

#include "FileSearcher.h"
#include "RegexParser.h"

void connect(QPointer<FileSearcher>& fileSearcher, QPointer<RegexParser>& regexParser)
{

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
		QObject::connect(fileSearcher, &FileSearcher::workFinished, fsThread, &QThread::quit);
		fsThread->start();

		QPointer<QThread> rpThread = new QThread();
		QPointer<RegexParser> regexParser = new RegexParser();
		regexParser->moveToThread(rpThread);
		QObject::connect(rpThread, &QThread::started, regexParser, &RegexParser::run);
		QObject::connect(regexParser, &RegexParser::workFinished, rpThread, &QThread::quit);
		rpThread->start();

		connect(fileSearcher, regexParser);

		w->show();
		int res = a.exec();

		fileSearcher->deleteLater();
		fsThread->wait();
		fsThread->deleteLater();

		regexParser->deleteLater();
		rpThread->wait();
		rpThread->deleteLater();

		w->deleteLater();

		return res;
	}
	catch (...)
	{
	}
	return -1;
}
