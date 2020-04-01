#include "RegexParser.h"

RegexParser::RegexParser()
{}

RegexParser::~RegexParser()
{
	emit workFinished();
}

void RegexParser::run()
{

}

void RegexParser::validateRegexp(RegexpValidateData data)
{
	data.isValid = true;
	QThread::msleep(500);
	emit regexpValidated(data);
}