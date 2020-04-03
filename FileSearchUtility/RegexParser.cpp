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
	data.isValid = parse(data.val);
	emit regexpValidated(data);
}

bool RegexParser::parse(const QString& data)
{
	return true;
}