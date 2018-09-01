#include "dbmsgbase.h"

#include <QDebug>

#include <algorithm>

#include "dbmsgfieldbase.h"

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
        qDebug() << iter.key() << iter.value()->toVariant() << iter.value()->touched();
}

void DbMsgBase::copyTo(QVariantMap &variantMap) const
{
    const auto fields = getFields();
    for(auto iter = fields.cbegin(); iter != fields.cend(); iter++)
    {
        const auto key = iter.key();
        const auto field = iter.value();
        const auto hasValue = field->hasValue();
        const auto variant = field->toVariant();
        if(hasValue)
            variantMap.insert(key, variant);
        else
            qWarning() << key << "has no value for full transmission!";
    }
}

void DbMsgBase::copyTouchedTo(QVariantMap &variantMap) const
{
    QStringList clearedFields;

    const auto fields = getFields();
    for(auto iter = fields.cbegin(); iter != fields.cend(); iter++)
        if(iter.value()->touched())
        {
            if(iter.value()->hasValue())
                variantMap.insert(iter.key(), iter.value()->toVariant());
            else
                clearedFields.append(iter.key());
        }

    if(!clearedFields.isEmpty())
        variantMap.insert(m_clearedFieldsName, clearedFields);
}
