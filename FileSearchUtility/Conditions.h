#pragma once

#include <QString>
#include <QStringList>
#include <QFileInfo>

class BaseCondition
{
public:
	BaseCondition();
	virtual ~BaseCondition();
	virtual bool check(const QFileInfo& v);
};

// ***************
// Name condition
// ***************
enum NAME_OPERATORS
{
	NO_NULL = -1,
	NO_EQUAL = 0,
	NO_CONT = 1
};

const QStringList NAME_OPERATOR_VALUES =
{
		"==",
		"contains"
};

class NameCondition : public BaseCondition
{
public:
	bool setOperator(const QString& v);
	void setValue(const QString& v);
	bool check(const QFileInfo& v) override;

private:
	NAME_OPERATORS cond = NAME_OPERATORS::NO_NULL;
	QString checkValue = "";
};

// ***************
// Size condition
// ***************

enum SIZE_OPERATORS
{
	SO_NULL = -1,
	SO_LESS = 0,
	SO_MORE = 1
};

const QStringList SIZE_OPERATOR_VALUES =
{
		"<",
		">"
};

struct SizeCondition : public BaseCondition
{
public:
	bool setOperator(const QString& v);
	void setValue(const quint64& v);
	bool check(const QFileInfo& v) override;
private:
	SIZE_OPERATORS cond = SIZE_OPERATORS::SO_NULL;
	quint64 checkValue = 0;
};

// *******************
// Attribute condition
// *******************

enum ATTRIBUTE_OPERATORS
{
	AO_NULL = -1,
	AO_IS = 0,
	AO_NOT = 1
};

const QStringList ATTRIBUTE_OPERATOR_VALUES =
{
		"is",
		"not"
};

enum ATTRIBUTES
{
	AV_HIDDEN = 0,
	AV_DIRECTORY = 1, 
	AV_READONLY = 2
};

const QStringList ATTRIBUTE_VALUES =
{
		"hidden",
		"hidden",
		"readonly"
};

struct AttributeCondition : public BaseCondition
{
public:
	bool setOperator(const QString& v);
	bool setValue(const QString& v);
	bool check(const QFileInfo& v) override;
private:
	ATTRIBUTE_OPERATORS cond = ATTRIBUTE_OPERATORS::AO_NULL;
	ATTRIBUTES checkValue = ATTRIBUTES::AV_HIDDEN;
};

// *******************
