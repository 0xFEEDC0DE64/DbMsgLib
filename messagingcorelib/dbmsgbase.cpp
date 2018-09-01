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

void DbMsgBase::apply(const QVariantMap &variantMap)
{
    const auto fields = getFields();
    for(auto iter = variantMap.cbegin(); iter != variantMap.cend(); iter++)
    {
        if(iter.key() == m_clearedFieldsName)
        {
            Q_ASSERT(iter.value().type() == QVariant::StringList);
            for(const auto &clearedField : iter.value().toStringList())
            {
                Q_ASSERT(fields.contains(clearedField));
                const auto field = fields.value(clearedField);
                if(field->touched())
                    qWarning() << "delta message contained field which has been touched!";
                field->clear();
                field->setTouched(false);
            }
        }
        else
        {
            Q_ASSERT(fields.contains(iter.key()));
            const auto field = fields.value(iter.key());
            if(field->touched())
                qWarning() << "delta message contained field which has been touched!";
            field->setVariant(iter.value());
            field->setTouched(false);
        }
    }
}
