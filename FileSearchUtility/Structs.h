#pragma once

#include <QString>
#include <QSharedPointer>
#include "Conditions.h"

struct RegexpTree
{
	QSharedPointer<BaseCondition> condition;
	QSharedPointer<RegexpTree> left;
	QSharedPointer<RegexpTree> right;
};

struct RegexpValidateData
{
	QString val;
	quint64 id = 0;
	bool res = false;
};

struct RegexpParsingData
{
	QString val;
	quint64 id = 0;

};