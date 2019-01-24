#include "ioWmiConverter.h"

namespace SDPO {

/******************************************************************/

IOWmiConverter::IOWmiConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOWmiConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TWmi();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOWmiConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::WMI)) {
        return false;
    }
    TWmi *test = qobject_cast<TWmi*>(m_TestMethod);
    if (key == SP_HOST) {
        test->setHost(value);
    } else if (key == SP_NAMESPACE) {
        test->setNameSpace(value);
    } else if (key == SP_QUERY) {
        test->setQuery(value);
    } else if (key == SP_ALERTIF) {
        test->setAlertIf(value);
    } else if (key == SP_ALERTIFCOMPARE) {
        test->setAlertIfCompare(value);
    } else if (key == SP_ALERTIFCOUNT) {
        test->setAlertIfCount(value);
    } else if (key == SP_IFINSTALLCHANGED) {
        test->setIfInstanChanged(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOWmiConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::WMI)) {
        return;
    }
    TWmi *test = qobject_cast<TWmi*>(m_TestMethod);
    out << SP_HOST              << " = " << test->getHost()             << endl;
    out << SP_NAMESPACE         << " = " << test->getNameSpace()        << endl;
    out << SP_QUERY             << " = " << test->getQuery()            << endl;
    out << SP_ALERTIF           << " = " << test->getAlertIf()          << endl;
    out << SP_ALERTIFCOMPARE    << " = " << test->getAlertIfCompare()   << endl;
    out << SP_ALERTIFCOUNT      << " = " << test->getAlertIfCount()     << endl;
    out << SP_IFINSTALLCHANGED  << " = " << test->getIfInstanChanged()  << endl;
}
/******************************************************************/

QJsonObject IOWmiConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::WMI)) {
        return jsonObj;
    }
    TWmi* test = qobject_cast<TWmi*>(m_TestMethod);
    jsonObj.insert(SP_HOST, QJsonValue(test->getHost()));
    jsonObj.insert(SP_NAMESPACE, QJsonValue(test->getNameSpace()));
    jsonObj.insert(SP_QUERY, QJsonValue(test->getQuery()));
    jsonObj.insert(SP_ALERTIF, QJsonValue(test->getAlertIf()));
    jsonObj.insert(SP_ALERTIFCOMPARE, QJsonValue(test->getAlertIfCompare()));
    jsonObj.insert(SP_ALERTIFCOUNT, QJsonValue(test->getAlertIfCount()));
    jsonObj.insert(SP_IFINSTALLCHANGED, QJsonValue(test->getIfInstanChanged()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOWmiConverter::fromJsonObject(QJsonObject jsonObj)
{
    TWmi *test = qobject_cast<TWmi*>(getTestMethod());
    test->setHost(jsonObj.value(SP_HOST).toString());
    test->setNameSpace(jsonObj.value(SP_NAMESPACE).toString());
    test->setQuery(jsonObj.value(SP_QUERY).toString());
    test->setAlertIf(jsonObj.value(SP_ALERTIF).toString());
    test->setAlertIfCompare(jsonObj.value(SP_ALERTIFCOMPARE).toString());
    test->setAlertIfCount(jsonObj.value(SP_ALERTIFCOUNT).toString());
    test->setIfInstanChanged(jsonObj.value(SP_IFINSTALLCHANGED).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO

