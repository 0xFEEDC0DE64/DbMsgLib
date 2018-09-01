#pragma once

#include <algorithm>

#include <QString>
#include <QDateTime>
#include <QMap>
#include <QVariant>
#include <QDebug>

class DbMsgFieldBase
{
public:
    DbMsgFieldBase() : m_touched(false) {}

    bool touched() const { return m_touched; }
    void setTouched(bool touched) { m_touched = touched; }

    virtual QVariant getVariant() const = 0;

private:
    bool m_touched;
};

template<typename T>
class DbMsgField : public DbMsgFieldBase
{
public:
    DbMsgField() : DbMsgFieldBase(), m_hasValue(false) {}
    DbMsgField(const T &value) : DbMsgFieldBase(), m_value(value), m_hasValue(true) {}

    T &getValue() { return m_value; }
    const T &getValue() const { return m_value; }
    void setValue(const T &value) { m_hasValue = true; m_value = value; setTouched(true); }

    bool hasValue() const { return m_hasValue; }

    QVariant getVariant() const { return getValue(); }

private:
    T m_value;
    bool m_hasValue;
};

class DbMsgBase
{
public:
    DbMsgBase() {}

    bool touched() const
    {
        const auto fields = getFields();
        return std::any_of(fields.cbegin(), fields.cend(), [](const DbMsgFieldBase *field) { return field->touched(); });
    }

    void setTouched(bool touched)
    {
        for(DbMsgFieldBase *field : getFields())
            field->setTouched(touched);
    }

    void debug() const
    {
        const auto fields = getFields();
        for(auto iter = fields.cbegin(); iter != fields.cend(); iter++)
            qDebug() << iter.key() << iter.value()->getVariant() << iter.value()->touched();
    }

protected:
    virtual QMap<QString, DbMsgFieldBase*> getFields() = 0;
    virtual QMap<QString, const DbMsgFieldBase*> getFields() const = 0;
};

class MyMessage : public DbMsgBase
{
public:
    MyMessage() : DbMsgBase() {}

    MyMessage(const QString &name, const QDate &birthday, const QDateTime &sendTimestamp, int age, double weight) :
        DbMsgBase(),
        m_name(name), m_birthday(birthday), m_sendTimestamp(sendTimestamp), m_age(age), m_weight(weight)
    {}

    QString getName() const { return m_name.getValue(); }
    void setName(const QString &name) { m_name.setValue(name); }
    DbMsgField<QString> &nameField() { return m_name; }
    const DbMsgField<QString> &nameField() const { return m_name; }
    DbMsgFieldBase &nameFieldBase() { return m_name; }
    const DbMsgFieldBase &nameFieldBase() const { return m_name; }

    QDate getBirthday() const { return m_birthday.getValue(); }
    void setBirthday(const QDate &birthday) { m_birthday.setValue(birthday); }
    DbMsgField<QDate> &birthdayField() { return m_birthday; }
    const DbMsgField<QDate> &birthdayField() const { return m_birthday; }
    DbMsgFieldBase &birthdayFieldBase() { return m_birthday; }
    const DbMsgFieldBase &birthdayFieldBase() const { return m_birthday; }

    QDateTime getSendTimestamp() const { return m_sendTimestamp.getValue(); }
    void setSendTimestamp(const QDateTime &sendTimestamp) { m_sendTimestamp.setValue(sendTimestamp); }
    DbMsgField<QDateTime> &sendTimestampField() { return m_sendTimestamp; }
    const DbMsgField<QDateTime> &sendTimestampField() const { return m_sendTimestamp; }
    DbMsgFieldBase &sendTimestampFieldBase() { return m_sendTimestamp; }
    const DbMsgFieldBase &sendTimestampFieldBase() const { return m_sendTimestamp; }

    int getAge() const { return m_age.getValue(); }
    void setAge(const int &age) { m_age.setValue(age); }
    DbMsgField<int> &ageField() { return m_age; }
    const DbMsgField<int> &ageField() const { return m_age; }
    DbMsgFieldBase &ageFieldBase() { return m_age; }
    const DbMsgFieldBase &ageFieldBase() const { return m_age; }

    double getWeight() const { return m_weight.getValue(); }
    void setWeight(const double &weight) { m_weight.setValue(weight); }
    DbMsgField<double> &weightField() { return m_weight; }
    const DbMsgField<double> &weightField() const { return m_weight; }
    DbMsgFieldBase &weightFieldBase() { return m_weight; }
    const DbMsgFieldBase &weightFieldBase() const { return m_weight; }

protected:
    QMap<QString, DbMsgFieldBase*> getFields() override
    {
        QMap<QString, DbMsgFieldBase*> fields;

        for(auto iter = m_fields.cbegin(); iter != m_fields.cend(); iter++)
            fields.insert(iter.key(), &(this->*iter.value())());

        return fields;
    }

    QMap<QString, const DbMsgFieldBase*> getFields() const override
    {
        QMap<QString, const DbMsgFieldBase*> fields;

        for(auto iter = m_fields.cbegin(); iter != m_fields.cend(); iter++)
            fields.insert(iter.key(), &(const_cast<MyMessage*>(this)->*iter.value())());

        return fields;
    }

private:
    typedef DbMsgFieldBase &(MyMessage::*FieldGetterMethod)();
    static const QMap<QString, FieldGetterMethod> m_fields;

    DbMsgField<QString> m_name;
    DbMsgField<QDate> m_birthday;
    DbMsgField<QDateTime> m_sendTimestamp;
    DbMsgField<int> m_age;
    DbMsgField<double> m_weight;
};
