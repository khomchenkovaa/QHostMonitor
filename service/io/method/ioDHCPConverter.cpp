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

}
/******************************************************************/


} //namespace SDPO
