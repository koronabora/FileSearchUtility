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

QString BaseCondition::OP_TYPE_NAME(const OPERATOR_TYPE& type)
{
	switch (type)
	{
	case OPERATOR_TYPE::ATTRIBUTE:
		return "ATTRIBUTE";
		break;
	case OPERATOR_TYPE::BASE:
		return "BASE";
		break;
	case OPERATOR_TYPE::LOGICAL:
		return "LOGICAL";
		break;
	case OPERATOR_TYPE::NAME:
		return "NAME";
		break;
	case OPERATOR_TYPE::SIZE:
		return "SIZE";
		break;
	};
	return QString();
}

// i think, this code is bad

QString BaseCondition::hideBracketsFromParams(const QString& in)
{
	QString buffer;
	bool inStringLiteral = false;
	for (size_t i = 0; i < in.size(); i++)
	{
		if (stringLiteralSymbols.contains(in.at(i)))
			inStringLiteral = !inStringLiteral;
		if (inStringLiteral &&specialSymbols.contains(in.at(i)))
		{
			buffer += specialSymbolsReplacers.at(specialSymbols.indexOf(in.at(i)));
		}
		else
			buffer += in.at(i);
	}
	return buffer;
}

QString BaseCondition::restoreBracketsToParams(const QString& in)
{
	QString buffer = in;	
	for (size_t i = 0; i < specialSymbolsReplacers.size(); i++)
		buffer = buffer.replace(specialSymbolsReplacers.at(i), QString(specialSymbols.at(i)));
	return buffer;
}

//**************************************

bool NameCondition::setOperator(const QString& v)
{
	int index = NAME_OPERATOR_VALUES.indexOf(v);
	if (index >= 0)
	{
		cond = NAME_OPERATORS(index);
		return true;
	}
	return false;
};

bool NameCondition::setValue(const QString& v)
{
	checkValue = v;
	if (checkValue.size() > 2)
	{
		checkValue = BaseCondition::restoreBracketsToParams(checkValue);

		QChar l = checkValue.at(0);
		QChar r = checkValue.at(checkValue.size() - 1);

		bool b0 = stringLiteralSymbols.contains(l);
		bool b1 = stringLiteralSymbols.contains(r);

		checkValue.remove(0, 1);
		checkValue.remove(checkValue.size()-1, 1);

		return b1 && b0;
	}
	return true;
};

bool NameCondition::check(const QFileInfo& v)
{
	QString f = v.fileName();
	if (cond == NAME_OPERATORS::NO_CONT)
		return f.contains(checkValue);
	else if (cond == NAME_OPERATORS::NO_EQUAL)
	{
		bool res = (f == checkValue);
		return res;

	}
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
		return true;
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
		return true;
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

OPERATOR_TYPE LogicalCondition::getType() { return OPERATOR_TYPE::LOGICAL; }

bool LogicalCondition::check(const bool& left, const bool& right)
{
	if (cond == LO_AND)
		return left && right;
	else if (cond == LO_OR)
		return left || right;
	return false;
}