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

QJsonObject IOMySqlConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MySQL)) {
        return jsonObj;
    }
    TMySql* test = qobject_cast<TMySql*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getHost()));
    jsonObj.insert(SP_PORT, QJsonValue(test->getPort()));
    jsonObj.insert(SP_DATABASE, QJsonValue(test->getDatabase()));
    jsonObj.insert(SP_USER, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOMySqlConverter::fromJsonObject(QJsonObject jsonObj)
{
    TMySql *test = qobject_cast<TMySql*>(getTestMethod());
    test->setHost(jsonObj.value(SP_SERVER).toString());
    test->setPort(jsonObj.value(SP_PORT).toInt());
    test->setDatabase(jsonObj.value(SP_DATABASE).toString());
    test->setLogin(jsonObj.value(SP_USER).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO
