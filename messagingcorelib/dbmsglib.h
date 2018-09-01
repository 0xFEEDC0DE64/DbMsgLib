#pragma once

#include <QVariant>
#include <QMap>
#include <QString>

class QJsonObject;

class DbMsgFieldBase
{
public:
    DbMsgFieldBase();
    virtual ~DbMsgFieldBase();

    bool hasValue() const;
    virtual void clear();

    bool touched() const;
    void setTouched(bool touched);

    virtual QVariant getVariant() const = 0;

protected:
    void setHasValue(bool hasValue);

private:
    bool m_hasValue;
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

    void clear() override;
    QVariant getVariant() const override;

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
QVariant DbMsgField<T>::getVariant() const
{
    return getValue();
}

class DbMsgBase
{
    static const QString m_clearedFieldsName;

public:
    DbMsgBase();
    virtual ~DbMsgBase();

    bool touched() const;

    void setTouched(bool touched);

    void debug() const;

    void copyTo(QJsonObject &jsonObject) const;
    void copyTo(QVariantMap &variantMap) const;

    void copyTouchedTo(QJsonObject &jsonObject) const;
    void copyTouchedTo(QVariantMap &variantMap) const;

protected:
    virtual QMap<QString, DbMsgFieldBase*> getFields() = 0;
    virtual QMap<QString, const DbMsgFieldBase*> getFields() const = 0;
};
