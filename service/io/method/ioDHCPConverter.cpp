#include "ioDHCPConverter.h"

namespace SDPO {

/******************************************************************/

IODHCPConverter::IODHCPConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IODHCPConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TDhcp();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IODHCPConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DHCP)) {
        return false;
    }
    TDhcp *test = qobject_cast<TDhcp*>(m_TestMethod);
    if (key == SP_HOST) {
        test->setHost(value);
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_REQUEST_IP) {
        test->setRequestIp(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IODHCPConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DHCP)) {
        return;
    }
    TDhcp*test = qobject_cast<TDhcp*>(m_TestMethod);
    out << SP_HOST      << " = " << test->getHost()           << endl;
    out << SP_TIMEOUT   << " = " << test->getTimeout()        << endl;
    if (test->getRequestIp() != DHCP_CURRENT_LOCAL_IP) {
        out << SP_REQUEST_IP << " = " << test->getRequestIp() << endl;
    }
}

/******************************************************************/

QJsonObject IODHCPConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DHCP)) {
        return jsonObj;
    }
    TDhcp* test = qobject_cast<TDhcp*>(m_TestMethod);
    jsonObj.insert(SP_HOST, QJsonValue(test->getHost()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    if (test->getRequestIp() != DHCP_CURRENT_LOCAL_IP) {
        jsonObj.insert(SP_REQUEST_IP, QJsonValue(test->getRequestIp()));
    }
    return jsonObj;
}

/******************************************************************/

TTestMethod *IODHCPConverter::fromJsonObject(QJsonObject jsonObj)
{
    TDhcp *test = qobject_cast<TDhcp*>(getTestMethod());
    test->setHost(jsonObj.value(SP_HOST).toString());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    if (jsonObj.contains(SP_REQUEST_IP)) {
        test->setRequestIp(jsonObj.value(SP_REQUEST_IP).toString());
    }
    return test;
}

/******************************************************************/

} //namespace SDPO
