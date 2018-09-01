#include "mymessage.h"

const QMap<QString, MyMessage::FieldGetterMethod> MyMessage::m_fields {
    { "name", &MyMessage::nameFieldBase },
    { "birthday", &MyMessage::birthdayFieldBase },
    { "sendTimestamp", &MyMessage::sendTimestampFieldBase },
    { "age", &MyMessage::ageFieldBase },
    { "weight", &MyMessage::weightFieldBase }
};
