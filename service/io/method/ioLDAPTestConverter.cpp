#include "ioLDAPTestConverter.h"

namespace SDPO {

/******************************************************************/

IOLDAPTestConverter::IOLDAPTestConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOLDAPTestConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TLdapTest();
    }
    return m_TestMethod;
}

/******************************************************************/

bool IOLDAPTestConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Ldap)) {
        return false;
    }
    TLdapTest *test = qobject_cast<TLdapTest*>(m_TestMethod);
    if (key == SP_HOST) {
        test->setHost(value);
    } else if (key == SP_PORT) {
        test->setPort(value.toInt());
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_LOGIN) {
        test->setLogin(value);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else if (key == SP_CHECKPERFORMSEARCH) {
        test->setCheckPerformSearch(value == "Yes");
    } else if (key == SP_BASEOBJECT) {
        test->setBaseObject(value);
    } else if (key == SP_RESLIMIT) {
        test->setResLimit(value.toInt());
    } else if (key == SP_SEARCHFILTER) {
        test->setSearchFilter(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOLDAPTestConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Ldap)) {
        return;
    }
    TLdapTest *test = qobject_cast<TLdapTest*>(m_TestMethod);
    out << SP_HOST                  << " = " << test->getHost()              << endl;
    out << SP_PORT                  << " = " << test->getPort()              << endl;
    out << SP_TIMEOUT               << " = " << test->getTimeout()           << endl;
    out << SP_LOGIN                 << " = " << test->getLogin()             << endl;
    out << SP_PASSWORD              << " = " << test->getPassword()          << endl;
    out << SP_CHECKPERFORMSEARCH    << " = " << test->isCheckPerformSearch() << endl;
    out << SP_BASEOBJECT            << " = " << test->getBaseObject()        << endl;
    out << SP_RESLIMIT              << " = " << test->getResLimit()          << endl;
    out << SP_SEARCHFILTER          << " = " << test->getSearchFilter()      << endl;
}

/******************************************************************/

QJsonObject IOLDAPTestConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Ldap)) {
        return jsonObj;
    }
    TLdapTest* test = qobject_cast<TLdapTest*>(m_TestMethod);
    jsonObj.insert(SP_HOST, QJsonValue(test->getHost()));
    jsonObj.insert(SP_PORT, QJsonValue(test->getPort()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_LOGIN, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    jsonObj.insert(SP_CHECKPERFORMSEARCH, QJsonValue(test->isCheckPerformSearch()));
    jsonObj.insert(SP_BASEOBJECT, QJsonValue(test->getBaseObject()));
    jsonObj.insert(SP_RESLIMIT, QJsonValue(test->getResLimit()));
    jsonObj.insert(SP_SEARCHFILTER, QJsonValue(test->getSearchFilter()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOLDAPTestConverter::fromJsonObject(QJsonObject jsonObj)
{
    TLdapTest *test = qobject_cast<TLdapTest*>(getTestMethod());
    test->setHost(jsonObj.value(SP_HOST).toString());
    test->setPort(jsonObj.value(SP_PORT).toInt());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setLogin(jsonObj.value(SP_LOGIN).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    test->setCheckPerformSearch(jsonObj.value(SP_CHECKPERFORMSEARCH).toBool());
    test->setBaseObject(jsonObj.value(SP_BASEOBJECT).toString());
    test->setResLimit(jsonObj.value(SP_RESLIMIT).toInt());
    test->setSearchFilter(jsonObj.value(SP_SEARCHFILTER).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO


