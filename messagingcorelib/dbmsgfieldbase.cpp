#include "dbmsgfieldbase.h"

DbMsgFieldBase::DbMsgFieldBase() :
    m_hasValue(false), m_touched(false)
{
}

DbMsgFieldBase::~DbMsgFieldBase()
{
}

bool DbMsgFieldBase::hasValue() const
{
    return m_hasValue;
}

void DbMsgFieldBase::clear()
{
    m_hasValue = false;
}

bool DbMsgFieldBase::touched() const
{
    return m_touched;
}

void DbMsgFieldBase::setTouched(bool touched)
{
    m_touched = touched;
}

void DbMsgFieldBase::setHasValue(bool hasValue)
{
    if(m_hasValue && !hasValue)
        clear();
    else
        m_hasValue = hasValue;
}
