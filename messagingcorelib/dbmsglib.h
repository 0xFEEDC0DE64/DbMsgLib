#pragma once

#include <QVariant>
#include <QMap>
#include <QString>

class DbMsgFieldBase
{
public:
    DbMsgFieldBase();
    virtual ~DbMsgFieldBase();

    bool touched() const;
    void setTouched(bool touched);

    virtual QVariant getVariant() const = 0;

private:
    bool m_touched;
};

template<typename T>
class DbMsgField : public DbMsgFieldBase
{
public:
    DbMsgField();
    DbMsgField(const T &value);

    T &getValue();
    const T &getValue() const;
    void setValue(const T &value);

    bool hasValue() const;

    QVariant getVariant() const;

private:
    T m_value;
    bool m_hasValue;
};

template<typename T>
DbMsgField<T>::DbMsgField() :
    DbMsgFieldBase(),
    m_hasValue(false)
{
}

template<typename T>
DbMsgField<T>::DbMsgField(const T &value) :
    DbMsgFieldBase(),
    m_value(value), m_hasValue(true)
{
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
    m_hasValue = true;
    m_value = value;
    setTouched(true);
}

template<typename T>
bool DbMsgField<T>::hasValue() const
{
    return m_hasValue;
}

template<typename T>
QVariant DbMsgField<T>::getVariant() const
{
    return getValue();
}

class DbMsgBase
{
public:
    DbMsgBase();
    virtual ~DbMsgBase();

    bool touched() const;

    void setTouched(bool touched);

    void debug() const;

protected:
    virtual QMap<QString, DbMsgFieldBase*> getFields() = 0;
    virtual QMap<QString, const DbMsgFieldBase*> getFields() const = 0;
};
