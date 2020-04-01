#include "Conditions.h"

BaseCondition::~BaseCondition()
{}

bool BaseCondition::check(const QFileInfo& v)
{
	bool res = true;
	return res;
}

bool NameCondition::setOperator(const QString& v)
{
	bool res = true;
	return res;
}

void NameCondition::setValue(const QString& v)
{
}

bool NameCondition::check(const QFileInfo& v)
{
	bool res = true;
	return res;
}

bool SizeCondition::setOperator(const QString& v)
{
	bool res = true;
	return res;
}

void SizeCondition::setValue(const quint64& v)
{}

bool SizeCondition::check(const QFileInfo& v)
{
	bool res = true;
	return res;
}

bool AttributeCondition::setOperator(const QString& v)
{
	bool res = true;
	return res;
}

bool AttributeCondition::setValue(const QString& v)
{
	bool res = true;
	return res;
}

bool AttributeCondition::check(const QFileInfo& v)
{
	bool res = true;
	return res;
}