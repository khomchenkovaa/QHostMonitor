#include "ioOracleConverter.h"

namespace SDPO {

/******************************************************************/

IOOracleConverter::IOOracleConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOOracleConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TOracle();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOOracleConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Oracle)) {
        return false;
    }
    TOracle *test = qobject_cast<TOracle*>(m_TestMethod);
    if (key == SP_SERVER) {
        test->setDatabase(value);
    } else if (key == SP_USER) {
        test->setLogin(value);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOOracleConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Oracle)) {
        return;
    }
    TOracle *test = qobject_cast<TOracle*>(m_TestMethod);
    out << SP_SERVER   << " = " << test->getDatabase() << endl;
    out << SP_USER     << " = " << test->getLogin()    << endl;
    out << SP_PASSWORD << " = " << test->getPassword() << endl;
}
/******************************************************************/


} // namespace SDPO
