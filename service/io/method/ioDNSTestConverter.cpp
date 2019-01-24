#include "ioDNSTestConverter.h"

namespace SDPO {

/******************************************************************/

IODNSTestConverter::IODNSTestConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IODNSTestConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TDnsTest();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IODNSTestConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DNS)) {
        return false;
    }
    TDnsTest *test = qobject_cast<TDnsTest*>(m_TestMethod);
    if (key == SP_SERVER) {
        test->setServer(value);
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_PROTOCOL) {
        test->setProtocol(value);
    } else if (key == SP_PORT) {
        test->setPort(value.toInt());
    } else if (key == SP_REQUEST) {
        test->setRequest(value);
    } else if (key == SP_REQUESTYPE) {
        test->setRequestType(value);
    } else if (key == SP_TESTRESULT) {
        test->setTestResultFor(true);
        test->setTestResult(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IODNSTestConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DNS)) {
        return;
    }
    TDnsTest*test = qobject_cast<TDnsTest*>(m_TestMethod);
    out << SP_SERVER        << " = " << test->getServer()         << endl;
    out << SP_TIMEOUT       << " = " << test->getTimeout()        << endl;
    out << SP_PROTOCOL      << " = " << test->getProtocol()       << endl;
    out << SP_PORT          << " = " << test->getPort()           << endl;
    out << SP_REQUEST       << " = " << test->getRequest()        << endl;
    out << SP_REQUESTYPE    << " = " << test->getRequestType()    << endl;
    if (test->isTestResultFor()) {
        out << SP_TESTRESULT       << " = " << test->getTestResult()        << endl;
    }

}
/******************************************************************/

QJsonObject IODNSTestConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DNS)) {
        return jsonObj;
    }
    TDnsTest* test = qobject_cast<TDnsTest*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getServer()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_PROTOCOL, QJsonValue(test->getProtocol()));
    jsonObj.insert(SP_PORT, QJsonValue(test->getPort()));
    jsonObj.insert(SP_REQUEST, QJsonValue(test->getRequest()));
    jsonObj.insert(SP_REQUESTYPE, QJsonValue(test->getRequestType()));
    if (test->isTestResultFor()) {
        jsonObj.insert(SP_TESTRESULT, QJsonValue(test->getTestResult()));
    }
    return jsonObj;
}

/******************************************************************/

TTestMethod *IODNSTestConverter::fromJsonObject(QJsonObject jsonObj)
{
    TDnsTest *test = qobject_cast<TDnsTest*>(getTestMethod());
    test->setServer(jsonObj.value(SP_SERVER).toString());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setProtocol(jsonObj.value(SP_PROTOCOL).toString());
    test->setPort(jsonObj.value(SP_PORT).toInt());
    test->setRequest(jsonObj.value(SP_REQUEST).toString());
    test->setRequestType(jsonObj.value(SP_REQUESTYPE).toString());
    if (test->isTestResultFor()) {
        test->setTestResult(jsonObj.value(SP_TESTRESULT).toString());
    }
    return test;
}

/******************************************************************/

} //namespace SDPO
