#pragma once

#include <QString>
#include <QVariantMap>
#include <QMap>

#include "messagingcorelib_global.h"

class DbMsgFieldBase;

#define DECLARE_DBFIELD(TYPE, NAME, UPPER_NAME) \
private: \
    DbMsgField<TYPE> m_##NAME;\
    \
public: \
    TYPE get##UPPER_NAME() const { return m_##NAME.getValue(); } \
    void set##UPPER_NAME(const TYPE &NAME) { m_##NAME.setValue(NAME); } \
    bool has##UPPER_NAME() const { return m_##NAME.hasValue(); } \
    void clear##UPPER_NAME() { m_##NAME.clear(); } \
    \
    DbMsgField<TYPE> &NAME##Field() { return m_##NAME; } \
    const DbMsgField<TYPE> &NAME##Field() const { return m_##NAME; } \
    DbMsgFieldBase &NAME##FieldBase() { return m_##NAME; } \
    const DbMsgFieldBase &NAME##FieldBase() const { return m_##NAME; }

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

    void apply(const QVariantMap &variantMap);

protected:
    virtual QMap<QString, DbMsgFieldBase*> getFields() = 0;
    virtual QMap<QString, const DbMsgFieldBase*> getFields() const = 0;
};
