#pragma once

#include <QString>
#include <QDateTime>
#include <QMap>

#include "dbmsglib.h"

class MyMessage : public DbMsgBase
{
    typedef DbMsgFieldBase &(MyMessage::*FieldGetterMethod)();
    static const QMap<QString, FieldGetterMethod> m_fields;

public:
    MyMessage();
    MyMessage(const QString &name, const QDate &birthday, const QDateTime &sendTimestamp, int age, double weight);

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
    QMap<QString, DbMsgFieldBase*> getFields() override;
    QMap<QString, const DbMsgFieldBase*> getFields() const override;

private:
    DbMsgField<QString> m_name;
    DbMsgField<QDate> m_birthday;
    DbMsgField<QDateTime> m_sendTimestamp;
    DbMsgField<int> m_age;
    DbMsgField<double> m_weight;
};
