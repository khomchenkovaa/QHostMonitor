#include "ioSnmpGetConverter.h"

namespace SDPO {

/******************************************************************/

IOSnmpGetConverter::IOSnmpGetConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOSnmpGetConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TSnmpGet();
    }
    return m_TestMethod;
}

/******************************************************************/

bool IOSnmpGetConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::SNMP)) {
        return false;
    }
    TSnmpGet *test = qobject_cast<TSnmpGet*>(m_TestMethod);
    if (key == SP_AGENT) {
        test->setHost(value);
    } else if (key == SP_COMMUNITY) {
        test->setCommunity(value);
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_RETRIES) {
        test->setRetries(value.toInt());
    } else if (key == SP_OID) {
        test->setMibOid(value);
    } else if (key == SP_VALUE) {
        test->setValue(value);
    } else if (key == SP_CONDITION) {
        TSnmpGet::Condition condition = test->getCondition();
        condition = test->conditionFromString(value, condition);
        test->setCondition(condition);
    } else {
        return false;
    }
    return true;

}

/******************************************************************/

void IOSnmpGetConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::SNMP)) {
        return;
    }
    TSnmpGet *test = qobject_cast<TSnmpGet*>(m_TestMethod);

    out << SP_AGENT     << " = " << test->getHost()                               << endl;
    out << SP_COMMUNITY << " = " << test->getCommunity()                          << endl;
    out << SP_TIMEOUT   << " = " << test->getTimeout() * 1000                     << endl;
    out << SP_OID       << " = " << test->getMibOid()                             << endl;
    out << SP_RETRIES   << " = " << test->getRetries()                            << endl;
    out << SP_VALUE     << " = " << test->getValue()                              << endl;
    out << SP_CONDITION << " = " << test->conditionToString(test->getCondition()) << endl;
}

/******************************************************************/

QJsonObject IOSnmpGetConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::SNMP)) {
        return jsonObj;
    }
    TSnmpGet* test = qobject_cast<TSnmpGet*>(m_TestMethod);
    jsonObj.insert(SP_AGENT, QJsonValue(test->getHost()));
    jsonObj.insert(SP_COMMUNITY, QJsonValue(test->getCommunity()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_RETRIES, QJsonValue(test->getRetries()));
    jsonObj.insert(SP_VALUE, QJsonValue(test->getValue()));
    jsonObj.insert(SP_OID, QJsonValue(test->getMibOid()));
    jsonObj.insert(SP_CONDITION, QJsonValue(test->conditionToString(test->getCondition())));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOSnmpGetConverter::fromJsonObject(QJsonObject jsonObj)
{
    TSnmpGet *test = qobject_cast<TSnmpGet*>(getTestMethod());
    test->setHost(jsonObj.value(SP_AGENT).toString());
    test->setCommunity(jsonObj.value(SP_COMMUNITY).toString());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setRetries(jsonObj.value(SP_RETRIES).toInt());
    test->setValue(jsonObj.value(SP_VALUE).toString());
    test->setMibOid(jsonObj.value(SP_OID).toString());
    TSnmpGet::Condition condition = test->getCondition();
    condition = test->conditionFromString(jsonObj.value(SP_CONDITION).toString(), condition);
    test->setCondition(condition);
    return test;
}
/******************************************************************/

} // namespace SDPO
