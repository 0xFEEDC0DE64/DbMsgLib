#include "mymessage.h"

IMPLEMENT_DBMESSAGE(MyMessage) {
    { "name", &MyMessage::nameFieldBase },
    { "birthday", &MyMessage::birthdayFieldBase },
    { "sendTimestamp", &MyMessage::sendTimestampFieldBase },
    { "age", &MyMessage::ageFieldBase },
    { "weight", &MyMessage::weightFieldBase }
};

MyMessage::MyMessage(const QString &name, const QDate &birthday, const QDateTime &sendTimestamp, int age, double weight) :
    DbMsgBase(),
    m_name(name), m_birthday(birthday), m_sendTimestamp(sendTimestamp), m_age(age), m_weight(weight)
{
}
