#include "Conditions.h"

BaseCondition::BaseCondition()
{
}

BaseCondition::~BaseCondition()
{};

bool BaseCondition::check(const QFileInfo& v)
{
	bool res = true;
	return res;
};

bool BaseCondition::setOperator(const QString& v)
{
	return true;
}

bool BaseCondition::setValue(const QString& v)
{
	return true;
}

OPERATOR_TYPE BaseCondition::getType() { return OPERATOR_TYPE::BASE; }

bool BaseCondition::check(const bool& left, const bool& right)
{
	return false;
}

//**************************************

bool NameCondition::setOperator(const QString& v)
{
	int index = NAME_OPERATOR_VALUES.indexOf(v);
	if (index >= 0)
	{
		cond = NAME_OPERATORS(index);
	}
	return false;
};

bool NameCondition::setValue(const QString& v)
{
	checkValue = v;
	return true;
};

bool NameCondition::check(const QFileInfo& v)
{
	if (cond == NAME_OPERATORS::NO_CONT)
		return v.fileName().contains(checkValue);
	else if (cond == NAME_OPERATORS::NO_EQUAL)
		return v.fileName().compare(checkValue) == 0;
	return false;
};

OPERATOR_TYPE NameCondition::getType() { return OPERATOR_TYPE::NAME; }

bool NameCondition::check(const bool& left, const bool& right)
{
	return false;
}

//**************************************

bool SizeCondition::setOperator(const QString& v)
{
	int index = SIZE_OPERATOR_VALUES.indexOf(v);
	if (index >= 0)
	{
		cond = SIZE_OPERATORS(index);
	}
	return false;
};

bool SizeCondition::setValue(const QString& v)
{
	bool ok;
	checkValue = v.toULongLong(&ok);
	return ok;
};

bool SizeCondition::check(const QFileInfo& v)
{
	if (cond == SIZE_OPERATORS::SO_LESS)
		return v.size() < checkValue;
	else if (cond == SIZE_OPERATORS::SO_MORE)
		return v.size() > checkValue;
	return false;
};

OPERATOR_TYPE SizeCondition::getType() { return OPERATOR_TYPE::SIZE; }

bool SizeCondition::check(const bool& left, const bool& right)
{
	return false;
}

//**************************************

bool AttributeCondition::setOperator(const QString& v)
{
	int index = ATTRIBUTE_OPERATOR_VALUES.indexOf(v);
	if (index >= 0)
	{
		cond = ATTRIBUTE_OPERATORS(index);
	}
	return false;
};

bool AttributeCondition::setValue(const QString& v)
{
	int index = ATTRIBUTE_VALUES.indexOf(v);
	if (index >= 0)
	{
		checkValue = ATTRIBUTES(index);
		return true;
	}
	return false;
};

bool AttributeCondition::check(const QFileInfo& v)
{
	if (cond == ATTRIBUTE_OPERATORS::AO_IS)
	{
		if (checkValue == ATTRIBUTES::AV_DIRECTORY)
			return v.isDir();
		else if (checkValue == ATTRIBUTES::AV_HIDDEN)
			return v.isHidden();
		else if (checkValue == ATTRIBUTES::AV_READONLY)
			return (!v.isWritable());
	}
	else if (cond == ATTRIBUTE_OPERATORS::AO_NOT)
	{ 
		if (checkValue == ATTRIBUTES::AV_DIRECTORY)
			return !v.isDir();
		else if (checkValue == ATTRIBUTES::AV_HIDDEN)
			return !v.isHidden();
		else if (checkValue == ATTRIBUTES::AV_READONLY)
			return (v.isWritable());
	}
		return false;
};

OPERATOR_TYPE AttributeCondition::getType() { return OPERATOR_TYPE::ATTRIBUTE; }

bool AttributeCondition::check(const bool& left, const bool& right)
{
	return false; 
}

//**************************************

bool LogicalCondition::setOperator(const QString& v) {
	cond = LOGICAL_OPERATORS(LOGICAL_OPERATOR_VALUES.indexOf(v));
	return true;
}

bool LogicalCondition::setValue(const QString& v) { return true; }

bool LogicalCondition::check(const QFileInfo& v) {
	return false;
}

OPERATOR_TYPE LogicalCondition::getType() {return OPERATOR_TYPE::LOGICAL;}

bool LogicalCondition::check(const bool& left, const bool& right)
{
	if (cond == LO_AND)
		return left && right;
	else if (cond == LO_OR)
		return left || right;
	return false;
}