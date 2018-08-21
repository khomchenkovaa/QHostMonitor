#include "ioMySqlConverter.h"

namespace SDPO {


/******************************************************************/

IOMySqlConverter::IOMySqlConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOMySqlConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TMySql();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOMySqlConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MySQL)) {
        return false;
    }
    TMySql *test = qobject_cast<TMySql*>(m_TestMethod);
    if (key == SP_SERVER) {
        test->setHost(value);
    } else if (key == SP_PORT) {
        test->setPort(value.toInt());
    } else if (key == SP_DATABASE) {
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

void IOMySqlConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MySQL)) {
        return;
    }
    TMySql *test = qobject_cast<TMySql*>(m_TestMethod);
    out << SP_SERVER   << " = " << test->getHost()     << endl;
    out << SP_PORT     << " = " << test->getPort()     << endl;
    out << SP_DATABASE << " = " << test->getDatabase() << endl;
    out << SP_USER     << " = " << test->getLogin()    << endl;
    out << SP_PASSWORD << " = " << test->getPassword() << endl;
}
/******************************************************************/

} //namespace SDPO
