#include "dbmsglib.h"

#include <QDebug>
#include <QJsonObject>
#include <QVariantMap>

#include <algorithm>

DbMsgFieldBase::DbMsgFieldBase() :
    m_hasValue(false), m_touched(false)
{
}

DbMsgFieldBase::~DbMsgFieldBase()
{
}

bool DbMsgFieldBase::hasValue() const
{
    return m_hasValue;
}

void DbMsgFieldBase::clear()
{
    m_hasValue = false;
}

bool DbMsgFieldBase::touched() const
{
    return m_touched;
}

void DbMsgFieldBase::setTouched(bool touched)
{
    m_touched = touched;
}

void DbMsgFieldBase::setHasValue(bool hasValue)
{
    if(m_hasValue && !hasValue)
        clear();
    else
        m_hasValue = hasValue;
}

const QString DbMsgBase::m_clearedFieldsName(QStringLiteral("__CLEARED_FIELDS"));

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
    {
        const auto key = iter.key();
        const auto field = iter.value();
        const auto hasValue = field->hasValue();
        const auto variant = field->getVariant();
        if(hasValue)
            variantMap.insert(key, variant);
        else
            qWarning() << key << "has no value for full transmission!";
    }
}

void DbMsgBase::copyTouchedTo(QJsonObject &jsonObject) const
{
    Q_UNUSED(jsonObject)
    qCritical() << "has not been implemented for json yet";
}

void DbMsgBase::copyTouchedTo(QVariantMap &variantMap) const
{
    QStringList clearedFields;

    const auto fields = getFields();
    for(auto iter = fields.cbegin(); iter != fields.cend(); iter++)
        if(iter.value()->touched())
        {
            if(iter.value()->hasValue())
                variantMap.insert(iter.key(), iter.value()->getVariant());
            else
                clearedFields.append(iter.key());
        }

    if(!clearedFields.isEmpty())
        variantMap.insert(m_clearedFieldsName, clearedFields);
}
