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
};

struct RegexpValidateData
{
	QString val;
	quint64 id = 0;
	bool isValid = false;
	RegexpTree result;
	bool check(const QFileInfo& v) const
	{
		bool res = true;

		return res;
	}
};
