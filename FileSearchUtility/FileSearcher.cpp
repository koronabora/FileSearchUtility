#include "FileSearcher.h"

FileSearcher::FileSearcher()
{}

FileSearcher::~FileSearcher()
{
	emit workFinished();
}

void FileSearcher::run()
{}

void FileSearcher::searchForFiles(const QString& path, const RegexpValidateData& regexp)
{}

void FileSearcher::stopSearch()
{}