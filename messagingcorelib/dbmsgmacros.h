#pragma once

#define DECLARE_DBFIELD(TYPE, NAME, UPPER_NAME) \
private: \
    DbMsgField<TYPE> m_##NAME;\
    \
public: \
    inline TYPE get##UPPER_NAME() const { return m_##NAME.getValue(); } \
    inline void set##UPPER_NAME(const TYPE &NAME) { m_##NAME.setValue(NAME); } \
    inline bool has##UPPER_NAME() const { return m_##NAME.hasValue(); } \
    inline void clear##UPPER_NAME() { m_##NAME.clear(); } \
    \
    inline DbMsgField<TYPE> &NAME##Field() { return m_##NAME; } \
    inline const DbMsgField<TYPE> &NAME##Field() const { return m_##NAME; } \
    inline DbMsgFieldBase &NAME##FieldBase() { return m_##NAME; } \
    inline const DbMsgFieldBase &NAME##FieldBase() const { return m_##NAME; }

#define DECLARE_DBMESSAGE(ClassName) \
public: \
    ClassName() = default; \
    ClassName(const ClassName &) = default; \
    ClassName(ClassName &&) = default; \
protected: \
    QMap<QString, DbMsgFieldBase*> getFields() override; \
    QMap<QString, const DbMsgFieldBase*> getFields() const override; \
private: \
    typedef DbMsgFieldBase &(ClassName::*FieldGetterMethod)(); \
    static const QMap<QString, FieldGetterMethod> ALL_FIELDS;

#define IMPLEMENT_DBMESSAGE(ClassName) \
    QMap<QString, DbMsgFieldBase *> ClassName::getFields() \
    { \
        QMap<QString, DbMsgFieldBase*> fields; \
        \
        for(auto iter = ALL_FIELDS.cbegin(); iter != ALL_FIELDS.cend(); iter++) \
            fields.insert(iter.key(), &(this->*iter.value())()); \
        \
        return fields; \
    } \
    \
    QMap<QString, const DbMsgFieldBase *> ClassName::getFields() const \
    { \
        QMap<QString, const DbMsgFieldBase*> fields; \
        \
        for(auto iter = ALL_FIELDS.cbegin(); iter != ALL_FIELDS.cend(); iter++) \
            fields.insert(iter.key(), &(const_cast<ClassName*>(this)->*iter.value())()); \
        \
        return fields; \
    } \
    \
    const QMap<QString, ClassName::FieldGetterMethod> ClassName::ALL_FIELDS
