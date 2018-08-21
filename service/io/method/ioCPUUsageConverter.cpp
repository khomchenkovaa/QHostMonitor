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

} //namespace SDPO
