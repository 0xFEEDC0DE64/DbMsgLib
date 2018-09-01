#pragma once

#include "dbmsgfieldbase.h"
#include "messagingcorelib_global.h"

template<typename T>
class DbMsgField : public DbMsgFieldBase
{
public:
    DbMsgField();
    DbMsgField(const T &value);

    T &getValue();
    const T &getValue() const;
    void setValue(const T &value);

    void clear() override;
    QVariant toVariant() const override;

private:
    T m_value;
};

template<typename T>
DbMsgField<T>::DbMsgField() :
    DbMsgFieldBase()
{
}

template<typename T>
DbMsgField<T>::DbMsgField(const T &value) :
    DbMsgFieldBase(),
    m_value(value)
{
    setHasValue(true);
}

template<typename T>
T &DbMsgField<T>::getValue()
{
    return m_value;
}

template<typename T>
const T &DbMsgField<T>::getValue() const
{
    return m_value;
}

template<typename T>
void DbMsgField<T>::setValue(const T &value)
{
    m_value = value;
    setHasValue(true);
    setTouched(true);
}

template<typename T>
void DbMsgField<T>::clear()
{
    DbMsgFieldBase::clear();
    m_value = T();
}

template<typename T>
QVariant DbMsgField<T>::toVariant() const
{
    return getValue();
}
