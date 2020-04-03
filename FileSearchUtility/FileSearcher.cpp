#include "FileSearcher.h"

FileSearcher::FileSearcher()
{}

FileSearcher::~FileSearcher()
{
	emit workFinished();

}

void FileSearcher::run()
{
	qt_ntfs_permission_lookup++;
}

void FileSearcher::searchForFiles(const QString& path, const RegexpValidateData& regexp)
{
	QStringList listOfDirs;
	QFileInfoList listOfFiles;
	listOfDirs.append(path);
	continueSearch = true;
	while (!listOfDirs.empty() || !listOfFiles.empty()) {
		if (!listOfFiles.empty()) // scan for files and subdirs
		{
			const QFileInfo info = listOfFiles.takeAt(0);
			if (regexp.check(info))
				haveSomeFile(info.filePath(), info.size());
		}
		else if (!listOfDirs.empty()) // scan dirs for new files
		{
			// search for first valid dir with files
			while (listOfFiles.empty())
			{
				if (listOfDirs.empty())
					break;
				QDir d(listOfDirs.takeAt(0));
				if (d.exists())
				{
					qDebug() << "Scanning dir: " << d.path();
					QFileInfoList list = d.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
					for (const QFileInfo& inf : list)
					{
						qDebug() << "Found entry: " << inf.filePath();
						if (inf.isDir())
						{
							listOfDirs.append(inf.filePath());
							qDebug() << "Added to directory list: " << inf.filePath();
						}
						else
						{
							listOfFiles.append(inf);
							qDebug() << "Added to file list: " << inf.filePath();
						}
					}
				}
			}
		}

		QCoreApplication::processEvents();
		if (!continueSearch)
		{
			break;
		}
	}
	emit searchFinished();
}

void FileSearcher::stopSearch()
{
	continueSearch = false;
}