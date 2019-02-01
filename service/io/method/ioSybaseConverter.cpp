#include "ioSybaseConverter.h"

namespace SDPO {

/******************************************************************/

IOSybaseConverter::IOSybaseConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOSybaseConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TSybase();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOSybaseConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Sybase)) {
        return false;
    }
    TSybase *test = qobject_cast<TSybase*>(m_TestMethod);
    if (key == SP_SERVER) {
        test->setServer(value);
    } else if (key == SP_DATABASE) {
        test->setDatabase(value);
    } else if (key == SP_LOGIN) {
        test->setLogin(value);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOSybaseConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Sybase)) {
        return;
    }
    TSybase *test = qobject_cast<TSybase*>(m_TestMethod);
    out << SP_SERVER   << " = " << test->getServer()   << endl;
    out << SP_DATABASE << " = " << test->getDatabase() << endl;
    out << SP_LOGIN    << " = " << test->getLogin()    << endl;
    out << SP_PASSWORD << " = " << test->getPassword() << endl;
}
/******************************************************************/

QJsonObject IOSybaseConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Sybase)) {
        return jsonObj;
    }
    TSybase* test = qobject_cast<TSybase*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getServer()));
    jsonObj.insert(SP_DATABASE, QJsonValue(test->getDatabase()));
    jsonObj.insert(SP_LOGIN, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOSybaseConverter::fromJsonObject(QJsonObject jsonObj)
{
    TSybase *test = qobject_cast<TSybase*>(getTestMethod());
    test->setServer(jsonObj.value(SP_SERVER).toString());
    test->setDatabase(jsonObj.value(SP_DATABASE).toString());
    test->setLogin(jsonObj.value(SP_LOGIN).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO
