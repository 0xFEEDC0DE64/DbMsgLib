#include "dbmsglib.h"

#include <QDebug>
#include <QJsonObject>
#include <QVariantMap>

#include <algorithm>

DbMsgFieldBase::DbMsgFieldBase() :
    m_touched(false)
{
}

DbMsgFieldBase::~DbMsgFieldBase()
{
}

bool DbMsgFieldBase::touched() const
{
    return m_touched;
}

void DbMsgFieldBase::setTouched(bool touched)
{
    m_touched = touched;
}

DbMsgBase::DbMsgBase()
{
}

DbMsgBase::~DbMsgBase()
{
}

bool DbMsgBase::touched() const
{
    const auto fields = getFields();
    return std::any_of(fields.cbegin(), fields.cend(), [](const DbMsgFieldBase *field) { return field->touched(); });
}

void DbMsgBase::setTouched(bool touched)
{
    for(DbMsgFieldBase *field : getFields())
        field->setTouched(touched);
}

void DbMsgBase::debug() const
{
    const auto fields = getFields();
    for(auto iter = fields.cbegin(); iter != fields.cend(); iter++)
        qDebug() << iter.key() << iter.value()->getVariant() << iter.value()->touched();
}

void DbMsgBase::copyTo(QJsonObject &jsonObject) const
{
    Q_UNUSED(jsonObject)
    qCritical() << "has not been implemented for json yet";
}

void DbMsgBase::copyTo(QVariantMap &variantMap) const
{
    const auto fields = getFields();
    for(auto iter = fields.cbegin(); iter != fields.cend(); iter++)
        variantMap.insert(iter.key(), iter.value()->getVariant());
}

void DbMsgBase::copyTouchedTo(QJsonObject &jsonObject) const
{
    Q_UNUSED(jsonObject)
    qCritical() << "has not been implemented for json yet";
}

void DbMsgBase::copyTouchedTo(QVariantMap &variantMap) const
{
    const auto fields = getFields();
    for(auto iter = fields.cbegin(); iter != fields.cend(); iter++)
        if(iter.value()->touched())
            variantMap.insert(iter.key(), iter.value()->getVariant());
}
