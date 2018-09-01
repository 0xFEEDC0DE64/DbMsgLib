#include "dbmsglib.h"

#include <QDebug>

#include <algorithm>

DbMsgFieldBase::DbMsgFieldBase() :
    m_touched(false)
{
}

DbMsgFieldBase::~DbMsgFieldBase()
{
}

bool DbMsgFieldBase::touched() const
{
    return m_touched;
}

void DbMsgFieldBase::setTouched(bool touched)
{
    m_touched = touched;
}

DbMsgBase::DbMsgBase()
{
}

DbMsgBase::~DbMsgBase()
{
}

bool DbMsgBase::touched() const
{
    const auto fields = getFields();
    return std::any_of(fields.cbegin(), fields.cend(), [](const DbMsgFieldBase *field) { return field->touched(); });
}

void DbMsgBase::setTouched(bool touched)
{
    for(DbMsgFieldBase *field : getFields())
        field->setTouched(touched);
}

void DbMsgBase::debug() const
{
    const auto fields = getFields();
    for(auto iter = fields.cbegin(); iter != fields.cend(); iter++)
        qDebug() << iter.key() << iter.value()->getVariant() << iter.value()->touched();
}
