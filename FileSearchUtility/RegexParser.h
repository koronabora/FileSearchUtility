#pragma once

#include <QObject>
#include <QThread>
#include <QDebug>
#include "Structs.h"

class RegexParser : public QObject
{
	Q_OBJECT
public:
	RegexParser();
	~RegexParser();

private:
	bool parse(QString data, QSharedPointer<RegexpTree>& result);

	// remove tail and head spaces and brackets
	QString clearVariable(const QString& s);
	QString clearSpaces(const QString& s);

	// parse <data> string for first occurence of operator (via operator names). Skips brackets. 
	// <resultOperator> - operator name which was found (index in <operatorVariants>)
	// <left> and <right> - parts of operator
	bool checkForOperator(QString data, const QStringList& operatorVariants, size_t& resultOperator, QString& left, QString& right);
	// parse not logical operator
	bool parseUnaryOperator(QString r, const QString& operatorName, QSharedPointer<BaseCondition>& res);
	bool checkBrackets(const QString& l, const QString& r);

public slots:
	void run();
	void validateRegexp(RegexpValidateData data);

signals:
	void workFinished();
	void regexpValidated(RegexpValidateData data);
	void setStatus(const QString& text);
};