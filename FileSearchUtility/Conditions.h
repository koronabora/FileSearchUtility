#pragma once

#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
#include <QVector>

static const QVector<QChar> stringLiteralSymbols = { '\"', 8220, 8221};
static const QVector<QChar> specialSymbols = { '(', ')'};
static const QStringList specialSymbolsReplacers = {"*|", "|*"};

enum OPERATOR_TYPE
{
	BASE = -1,
	LOGICAL = 0,
	NAME,
	SIZE,
	ATTRIBUTE
};

class BaseCondition
{
public:
	BaseCondition();
	virtual ~BaseCondition();
	virtual bool setOperator(const QString& v); // set operator type
	virtual bool setValue(const QString& v); // set check value
	virtual bool check(const QFileInfo& v); // check for the file
	virtual bool check(const bool& left, const bool& right); // check for 2 other leafs
	virtual OPERATOR_TYPE getType(); // get type of the operator 
	static QString OP_TYPE_NAME(const OPERATOR_TYPE& type);
	static QString hideBracketsFromParams(const QString& in);
	static QString restoreBracketsToParams(const QString& in);
};


// ***************
// logical condition
// ***************

enum LOGICAL_OPERATORS
{
	LO_NULL = -1,
	LO_AND = 0,
	LO_OR = 1
};

const QStringList LOGICAL_OPERATOR_VALUES =
{
		" and ",
		" or "
};

class LogicalCondition : public BaseCondition
{
public:
	bool setOperator(const QString& v) override;
	bool setValue(const QString& v) override;
	bool check(const QFileInfo& v) override;
	OPERATOR_TYPE getType() override;
	bool check(const bool& left, const bool& right) override;
private:
	LOGICAL_OPERATORS cond = LOGICAL_OPERATORS::LO_NULL;
};

// ***************
// Name condition
// ***************
const QString NAME_OPERATOR_LEFT = "name";

enum NAME_OPERATORS
{
	NO_NULL = -1,
	NO_EQUAL = 0,
	NO_CONT = 1
};

const QStringList NAME_OPERATOR_VALUES =
{
		" == ",
		" contains "
};

class NameCondition : public BaseCondition
{
public:
	bool setOperator(const QString& v) override ;
	bool setValue(const QString& v) override ;
	bool check(const QFileInfo& v) override;
	OPERATOR_TYPE getType() override;
	bool check(const bool& left, const bool& right) override;
private:
	NAME_OPERATORS cond = NAME_OPERATORS::NO_NULL;
	QString checkValue = "";
};

// ***************
// Size condition
// ***************

const QString SIZE_OPERATOR_LEFT = "size";

enum SIZE_OPERATORS
{
	SO_NULL = -1,
	SO_LESS = 0,
	SO_MORE = 1
};

const QStringList SIZE_OPERATOR_VALUES =
{
		" < ",
		" > "
};

struct SizeCondition : public BaseCondition
{
public:
	bool setOperator(const QString& v);
	bool setValue(const QString& v);
	bool check(const QFileInfo& v) override;
	OPERATOR_TYPE getType() override;
	bool check(const bool& left, const bool& right) override;
private:
	SIZE_OPERATORS cond = SIZE_OPERATORS::SO_NULL;
	quint64 checkValue = 0;
};

// *******************
// Attribute condition
// *******************

const QString ATTRIBUTE_OPERATOR_LEFT = "attribute";

enum ATTRIBUTE_OPERATORS
{
	AO_NULL = -1,
	AO_IS = 0,
	AO_NOT = 1
};

const QStringList ATTRIBUTE_OPERATOR_VALUES =
{
		" is ",
		" not "
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
		"directory",
		"readonly"
};

struct AttributeCondition : public BaseCondition
{
public:
	bool setOperator(const QString& v) override;
	bool setValue(const QString& v) override;
	bool check(const QFileInfo& v) override;
	OPERATOR_TYPE getType() override;
	bool check(const bool& left, const bool& right) override;
private:
	ATTRIBUTE_OPERATORS cond = ATTRIBUTE_OPERATORS::AO_NULL;
	ATTRIBUTES checkValue = ATTRIBUTES::AV_HIDDEN;
};

// *******************
