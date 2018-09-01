#pragma once

#include <QString>
#include <QVariantMap>
#include <QMap>

#include "messagingcorelib_global.h"

class DbMsgFieldBase;

class MESSAGINGCORELIBSHARED_EXPORT DbMsgBase
{
    static const QString m_clearedFieldsName;

public:
    DbMsgBase();
    virtual ~DbMsgBase();

    bool touched() const;

    void setTouched(bool touched);

    void debug() const;

    void copyTo(QVariantMap &variantMap) const;
    void copyTouchedTo(QVariantMap &variantMap) const;

protected:
    virtual QMap<QString, DbMsgFieldBase*> getFields() = 0;
    virtual QMap<QString, const DbMsgFieldBase*> getFields() const = 0;
};
