#pragma once

#include <QString>
#include <QDateTime>
#include <QMap>

#include "dbmsgbase.h"
#include "messagingcorelib_global.h"
#include "dbmsgfield.h"

class DbMsgFieldBase;

class MESSAGINGCORELIBSHARED_EXPORT MyMessage : public DbMsgBase
{
    DECLARE_DBMESSAGE(MyMessage)

public:
    MyMessage(const QString &name, const QDate &birthday, const QDateTime &sendTimestamp, int age, double weight);

    DECLARE_DBFIELD(QString, name, Name)
    DECLARE_DBFIELD(QDate, birthday, Birthday)
    DECLARE_DBFIELD(QDateTime, sendTimestamp, SendTimestamp)
    DECLARE_DBFIELD(int, age, Age)
    DECLARE_DBFIELD(double, weight, Weight)
};
