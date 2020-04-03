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
			r= right->check(v);
		// check current
		if (cond)
		{
			bool check0 = cond->check(v); // works with file operators
			bool check1 = cond->check(l, r); // wotks with logical operator
			qDebug() << "File = " << v.filePath() << " | c0 = " << check0 <<" | c1 = " << check1 << " | check = " << BaseCondition::OP_TYPE_NAME(cond->getType());
			return check0 || check1;
		}
		qDebug() << "File = " << v.filePath() << " | cond is null.";
		return false;
	}
};

struct RegexpValidateData
{
	QString val;
	quint64 id = 0;
	bool isValid = false;
	QSharedPointer<RegexpTree> result;
};
