#pragma once

#include <QString>
#include <QSharedPointer>
#include <QVector>
#include "Conditions.h"

struct RegexpTree
{
	QSharedPointer<BaseCondition> conditions;

	QSharedPointer<RegexpTree> left;
	QSharedPointer<RegexpTree> right;
	bool check(const QFileInfo& v) const
	{
		bool res = true;
		if (conditions)
			conditions->check(v);
		if ()
		return res;
	}
};

struct RegexpValidateData
{
	QString val;
	quint64 id = 0;
	bool isValid = false;
	RegexpTree result;
	
};
