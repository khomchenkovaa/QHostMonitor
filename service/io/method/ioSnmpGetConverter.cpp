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
    out << SP_RETRIES   << " = " << test->getRetries()                            << endl;
    out << SP_VALUE     << " = " << test->getValue()                              << endl;
    out << SP_CONDITION << " = " << test->conditionToString(test->getCondition()) << endl;
}

/******************************************************************/

} // namespace SDPO
