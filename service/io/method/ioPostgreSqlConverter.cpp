#include "ioPostgreSqlConverter.h"

namespace SDPO {

/******************************************************************/

IOPostgreSqlConverter::IOPostgreSqlConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOPostgreSqlConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TPostgreSql();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOPostgreSqlConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Postgre)) {
        return false;
    }
    TPostgreSql *test = qobject_cast<TPostgreSql*>(m_TestMethod);
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

void IOPostgreSqlConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Postgre)) {
        return;
    }
    TPostgreSql *test = qobject_cast<TPostgreSql*>(m_TestMethod);
    out << SP_SERVER   << " = " << test->getHost()     << endl;
    out << SP_PORT     << " = " << test->getPort()     << endl;
    out << SP_DATABASE << " = " << test->getDatabase() << endl;
    out << SP_USER     << " = " << test->getLogin()    << endl;
    out << SP_PASSWORD << " = " << test->getPassword() << endl;
}
/******************************************************************/

QJsonObject IOPostgreSqlConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Postgre)) {
        return jsonObj;
    }
    TPostgreSql* test = qobject_cast<TPostgreSql*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getHost()));
    jsonObj.insert(SP_PORT, QJsonValue(test->getPort()));
    jsonObj.insert(SP_DATABASE, QJsonValue(test->getDatabase()));
    jsonObj.insert(SP_USER, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOPostgreSqlConverter::fromJsonObject(QJsonObject jsonObj)
{
    TPostgreSql *test = qobject_cast<TPostgreSql*>(getTestMethod());
    test->setHost(jsonObj.value(SP_SERVER).toString());
    test->setPort(jsonObj.value(SP_PORT).toInt());
    test->setDatabase(jsonObj.value(SP_DATABASE).toString());
    test->setLogin(jsonObj.value(SP_USER).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO
