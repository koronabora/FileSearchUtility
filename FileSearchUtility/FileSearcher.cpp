#include "FileSearcher.h"

FileSearcher::FileSearcher()
{}

FileSearcher::~FileSearcher()
{
	emit workFinished();
}

void FileSearcher::run()
{}