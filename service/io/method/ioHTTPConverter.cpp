#include "ioHTTPConverter.h"

namespace SDPO {

/******************************************************************/

IOHTTPConverter::IOHTTPConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOHTTPConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new THttp();
    }
    return m_TestMethod;
}

/******************************************************************/

bool IOHTTPConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::HTTP)) {
        return false;
    }
    THttp *test = qobject_cast<THttp*>(m_TestMethod);
    if (key == SP_PROXY) {
        test->setProxy(value);
    } else if (key == SP_URL) {
        test->setUrl(value);
    } else if (key == SP_REQUEST) {
        test->setRequest(value);
    } else if (key == SP_FOLLOWREDIRECT) {
        test->setFollowRedirect(value == "Yes");
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOHTTPConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::HTTP)) {
        return;
    }
    THttp *test = qobject_cast<THttp*>(m_TestMethod);
    out << SP_PROXY              << " = " << test->getProxy()           << endl;
    out << SP_URL                << " = " << test->getUrl()             << endl;
    out << SP_REQUEST            << " = " << test->getRequest()         << endl;
    out << SP_FOLLOWREDIRECT     << " = " << test->isFollowRedirect()   << endl;
    out << SP_TIMEOUT            << " = " << test->getTimeout()         << endl;
}

/******************************************************************/

QJsonObject IOHTTPConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::HTTP)) {
        return jsonObj;
    }
    THttp* test = qobject_cast<THttp*>(m_TestMethod);
    jsonObj.insert(SP_PROXY, QJsonValue(test->getProxy()));
    jsonObj.insert(SP_URL, QJsonValue(test->getUrl()));
    jsonObj.insert(SP_REQUEST, QJsonValue(test->getRequest()));
    jsonObj.insert(SP_FOLLOWREDIRECT, QJsonValue(test->isFollowRedirect()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOHTTPConverter::fromJsonObject(QJsonObject jsonObj)
{
    THttp *test = qobject_cast<THttp*>(getTestMethod());
    test->setProxy(jsonObj.value(SP_PROXY).toString());
    test->setUrl(jsonObj.value(SP_URL).toString());
    test->setRequest(jsonObj.value(SP_REQUEST).toString());
    test->setFollowRedirect(jsonObj.value(SP_FOLLOWREDIRECT).toBool());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    return test;
}

/******************************************************************/

} //namespace SDPO

