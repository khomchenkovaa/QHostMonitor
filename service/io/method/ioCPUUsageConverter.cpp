#include "ioCPUUsageConverter.h"

namespace SDPO {

/******************************************************************/

IOCPUUsageConverter::IOCPUUsageConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOCPUUsageConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TCpuUsage();
    }
    return m_TestMethod;
}

/******************************************************************/

bool IOCPUUsageConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CPU)) {
        return false;
    }
    TCpuUsage *test = qobject_cast<TCpuUsage*>(m_TestMethod);
    if (key == SP_COMPUTER) {
        test->setComputer(value);
    } else if (key == SP_OS) {
        test->setOsSelect(value);
    } else if (key == SP_MAXCPUUSAGE) {
        test->setAlertWhen(value.toInt());
    } else if (key == SP_USERNAME) {
        test->setLogin(value);
        test->setConnectAs(true);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOCPUUsageConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CPU)) {
        return;
    }
    TCpuUsage*test = qobject_cast<TCpuUsage*>(m_TestMethod);
    out << SP_COMPUTER    << " = " << test->getComputer()           << endl;
    out << SP_OS          << " = " << test->getOsSelect()           << endl;
    out << SP_MAXCPUUSAGE << " = " << test->getAlertWhen()          << endl;
    if (test->isConnectAs()) {
        out << SP_USERNAME    << " = " << test->getLogin()          << endl;
        out << SP_PASSWORD    << " = " << test->getPassword()       << endl;
    }
}

/******************************************************************/

QJsonObject IOCPUUsageConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::CPU)) {
        return jsonObj;
    }
    TCpuUsage* test = qobject_cast<TCpuUsage*>(m_TestMethod);
    jsonObj.insert(SP_COMPUTER, QJsonValue(test->getComputer()));
    jsonObj.insert(SP_OS, QJsonValue(test->getOsSelect()));
    jsonObj.insert(SP_MAXCPUUSAGE, QJsonValue(test->getAlertWhen()));
    if (test->isConnectAs()) {
        jsonObj.insert(SP_USERNAME, QJsonValue(test->getLogin()));
        jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
        }
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOCPUUsageConverter::fromJsonObject(QJsonObject jsonObj)
{
    TCpuUsage *test = qobject_cast<TCpuUsage*>(getTestMethod());
    test->setComputer(jsonObj.value(SP_COMPUTER).toString());
    test->setOsSelect(jsonObj.value(SP_OS).toString());
    test->setAlertWhen(jsonObj.value(SP_MAXCPUUSAGE).toInt());
    test->setConnectAs(jsonObj.contains(SP_USERNAME));
    if (test->isConnectAs()) {
        test->setLogin(jsonObj.value(SP_USERNAME).toString());
        test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    }
    return test;
}

/******************************************************************/

} //namespace SDPO
