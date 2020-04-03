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
	data.val = BaseCondition::hideBracketsFromParams(data.val);
	data.isValid = parse(data.val, data.result);
	emit regexpValidated(data);
}

QString RegexParser::clearSpaces(const QString& s)
{
	QString data = s;
	// clear for first and last spaces
	while (data.size() > 0 && data.at(0) == ' ')
		data = data.remove(0, 1);
	while (data.size() > 0 && data.at(data.size() - 1) == ' ')
		data = data.remove(data.size() - 1, 1);
	return data;
}

QString RegexParser::clearVariable(const QString& s)
{

	QString data = clearSpaces(s);
	// clear for brackets
	if (data.size() > 1 && data.at(0) == '(' && data.at(data.size() - 1) == ')')
	{
		int bc = 0;
		bool isOk = true;
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data.at(i) == '(')
				bc++;
			else if (data.at(i) == ')')
				bc--;
			if (bc == 0 && i != (data.size()-1))
				isOk = false; // closing bracket for our first bracket is not at the end
		}
		if (isOk)
		{
			data = data.remove(0, 1);
			data = data.remove(data.size() - 1, 1);
		}
	}
	data = clearSpaces(data);
	return data;
}

bool RegexParser::checkBrackets(const QString& l, const QString& r)
{
	int c1 = l.count(')');
	int c2 = l.count('(');
	int c3 = r.count(')');
	int c4 = r.count('(');
	return c1 == c2 && c3 == c4;
}

bool RegexParser::checkForOperator(QString data, const QStringList& operatorVariants, size_t& resultOperator, QString& left, QString& right)
{
	data = clearVariable(data);

	if (data.size() > 2)
	{
		// 1st- check validate brackets
		int leftBrackets = data.count('(');
		int rightBrackets = data.count(')');

		if (leftBrackets != rightBrackets) // check for invalid bracket
			return false;
		else
		{
			// scan for operator
			for (size_t i = 0; i < operatorVariants.size(); i++)
			{
				const size_t size = data.split(operatorVariants.at(i)).size();
				for (size_t j = 0; j < size - 1; j++)
				{
					QString l = clearVariable(data.section(operatorVariants.at(i), 0, j));
					QString r = clearVariable(data.section(operatorVariants.at(i), j + 1, size - 1));
					qDebug() << " -> " << data << " | l = " << l << " | r = " << r << " | operator = " << operatorVariants.at(i);
					if (checkBrackets(l, r))
					{
						resultOperator = i;
						left = l;
						right = r;
						qDebug() << "ok!";
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool RegexParser::parseUnaryOperator(QString r, const QString& operatorName, QSharedPointer<BaseCondition>& res)
{
	r = clearVariable(r);
	bool b1 = res->setOperator(operatorName);
	bool b2 = res->setValue(r);
	return b1 && b2;
}

bool RegexParser::parse(QString data, QSharedPointer<RegexpTree>& result)
{
	// clear variable

	size_t resultOperator = 0;
	QString left, right;

	if (checkForOperator(data, LOGICAL_OPERATOR_VALUES, resultOperator, left, right))
	{
		// logical pair
		if (!result)
			result = QSharedPointer<RegexpTree>(new RegexpTree());

		result->cond = QSharedPointer<BaseCondition>(new LogicalCondition());
		result->cond->setOperator(LOGICAL_OPERATOR_VALUES.at(resultOperator));

		bool ok1 = parse(left, result->left);
		bool ok2 = parse(right, result->right);
		return ok1 && ok2;
	}
	else if (checkForOperator(data, NAME_OPERATOR_VALUES, resultOperator, left, right))
	{
		// name operator
		left = clearVariable(left);
		if (left.isEmpty() || right.isEmpty())
			return false;
		if (NAME_OPERATOR_LEFT.compare(left) != 0)
			return false;
		if (!result)
			result = QSharedPointer<RegexpTree>(new RegexpTree());
		result->cond = QSharedPointer<BaseCondition>(new NameCondition());
		return parseUnaryOperator(right, NAME_OPERATOR_VALUES.at(resultOperator), result->cond);

	}
	else if (checkForOperator(data, SIZE_OPERATOR_VALUES, resultOperator, left, right))
	{
		// size operator
		left = clearVariable(left);
		if (left.isEmpty() || right.isEmpty())
			return false;
		if (SIZE_OPERATOR_LEFT.compare(left) != 0)
			return false;
		if (!result)
			result = QSharedPointer<RegexpTree>(new RegexpTree());
		result->cond = QSharedPointer<BaseCondition>(new SizeCondition());
		return parseUnaryOperator(right, SIZE_OPERATOR_VALUES.at(resultOperator), result->cond);

	}
	else if (checkForOperator(data, ATTRIBUTE_OPERATOR_VALUES, resultOperator, left, right))
	{
		// attribute operator
		left = clearVariable(left);
		if (left.isEmpty() || right.isEmpty())
			return false;
		if (ATTRIBUTE_OPERATOR_LEFT.compare(left) != 0)
			return false;
		if (!result)
			result = QSharedPointer<RegexpTree>(new RegexpTree());
		result->cond = QSharedPointer<BaseCondition>(new AttributeCondition());
		return parseUnaryOperator(right, ATTRIBUTE_OPERATOR_VALUES.at(resultOperator), result->cond);
	}
	else
		return false;

	return false;
}