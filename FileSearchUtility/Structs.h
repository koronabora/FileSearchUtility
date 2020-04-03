#pragma once

#include <QString>
#include <QSharedPointer>
#include <QVector>
#include "Conditions.h"

struct RegexpTree
{
	QSharedPointer<BaseCondition> cond;

	QSharedPointer<RegexpTree> left;
	QSharedPointer<RegexpTree> right;
	bool check(const QFileInfo& v) const
	{
		// check left node
		bool l = false;
		if (left)
			l = left->check(v);
		// check right node
		bool r = false;
		if (right)
			right->check(v);
		// check current
		if (cond)
		{
			bool check0 = cond->check(v); // works with file operators
			bool check1 = cond->check(l, r); // wotks with logical operator
			return check0 || check1;
		}
		return false;
	}
};

struct RegexpValidateData
{
	QString val;
	quint64 id = 0;
	bool isValid = false;
	RegexpTree result;
};
