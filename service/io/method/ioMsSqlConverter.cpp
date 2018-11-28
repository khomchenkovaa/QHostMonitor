#include "ioMsSqlConverter.h"

namespace SDPO {


/******************************************************************/

IOMsSqlConverter::IOMsSqlConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOMsSqlConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TMsSql();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOMsSqlConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MSSQL)) {
        return false;
    }
    TMsSql *test = qobject_cast<TMsSql*>(m_TestMethod);
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

void IOMsSqlConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MSSQL)) {
        return;
    }
    TMsSql *test = qobject_cast<TMsSql*>(m_TestMethod);
    out << SP_SERVER   << " = " << test->getServer()   << endl;
    out << SP_DATABASE << " = " << test->getDatabase() << endl;
    out << SP_LOGIN    << " = " << test->getLogin()    << endl;
    out << SP_PASSWORD << " = " << test->getPassword() << endl;
}
/******************************************************************/

QJsonObject IOMsSqlConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MSSQL)) {
        return jsonObj;
    }
    TMsSql* test = qobject_cast<TMsSql*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getServer()));
    jsonObj.insert(SP_DATABASE, QJsonValue(test->getDatabase()));
    jsonObj.insert(SP_LOGIN, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOMsSqlConverter::fromJsonObject(QJsonObject jsonObj)
{
    TMsSql *test = qobject_cast<TMsSql*>(getTestMethod());
    test->setServer(jsonObj.value(SP_SERVER).toString());
    test->setDatabase(jsonObj.value(SP_DATABASE).toString());
    test->setLogin(jsonObj.value(SP_LOGIN).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO

