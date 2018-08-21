#include "ioInterbaseConverter.h"

namespace SDPO {


/******************************************************************/

IOInterbaseConverter::IOInterbaseConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOInterbaseConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TInterbase();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOInterbaseConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Interbase)) {
        return false;
    }
    TInterbase *test = qobject_cast<TInterbase*>(m_TestMethod);
    if (key == SP_SERVER) {
        test->setHost(value);
    } else if (key == SP_DATABASE) {
        test->setDatabase(value);
    } else if (key == SP_USER) {
        test->setLogin(value);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else if (key == SP_PROTOCOL) {
        test->setProtocol(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOInterbaseConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Interbase)) {
        return;
    }
    TInterbase *test = qobject_cast<TInterbase*>(m_TestMethod);
    out << SP_SERVER   << " = " << test->getHost()     << endl;
    out << SP_DATABASE << " = " << test->getDatabase() << endl;
    out << SP_USER     << " = " << test->getLogin()    << endl;
    out << SP_PASSWORD << " = " << test->getPassword() << endl;
    out << SP_PROTOCOL << " = " << test->getProtocol() << endl;

}
/******************************************************************/

} //namespace SDPO
