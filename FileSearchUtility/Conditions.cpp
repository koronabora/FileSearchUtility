#include "Conditions.h"

BaseCondition::~BaseCondition()
{}

bool BaseCondition::check(const QFileInfo& v)
{}

bool NameCondition::setOperator(const QString& v)
{}

void NameCondition::setValue(const QString& v)
{}

bool NameCondition::check(const QFileInfo& v)
{}

bool SizeCondition::setOperator(const QString& v)
{}

void SizeCondition::setValue(const quint64& v)
{}

bool SizeCondition::check(const QFileInfo& v)
{}

bool AttributeCondition::setOperator(const QString& v)
{}

bool AttributeCondition::setValue(const QString& v)
{}

bool AttributeCondition::check(const QFileInfo& v)
{}