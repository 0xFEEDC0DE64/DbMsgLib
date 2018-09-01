#include "mymessage.h"

const QMap<QString, MyMessage::FieldGetterMethod> MyMessage::m_fields {
    { "name", &MyMessage::nameFieldBase },
    { "birthday", &MyMessage::birthdayFieldBase },
    { "sendTimestamp", &MyMessage::sendTimestampFieldBase },
    { "age", &MyMessage::ageFieldBase },
    { "weight", &MyMessage::weightFieldBase }
};

MyMessage::MyMessage() :
    DbMsgBase()
{
}

MyMessage::MyMessage(const QString &name, const QDate &birthday, const QDateTime &sendTimestamp, int age, double weight) :
    DbMsgBase(),
    m_name(name), m_birthday(birthday), m_sendTimestamp(sendTimestamp), m_age(age), m_weight(weight)
{
}

QMap<QString, DbMsgFieldBase *> MyMessage::getFields()
{
    QMap<QString, DbMsgFieldBase*> fields;

    for(auto iter = m_fields.cbegin(); iter != m_fields.cend(); iter++)
        fields.insert(iter.key(), &(this->*iter.value())());

    return fields;
}

QMap<QString, const DbMsgFieldBase *> MyMessage::getFields() const
{
    QMap<QString, const DbMsgFieldBase*> fields;

    for(auto iter = m_fields.cbegin(); iter != m_fields.cend(); iter++)
        fields.insert(iter.key(), &(const_cast<MyMessage*>(this)->*iter.value())());

    return fields;
}
