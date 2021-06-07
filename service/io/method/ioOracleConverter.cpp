#include "ioOracleConverter.h"

namespace SDPO {

/******************************************************************/

IOOracleConverter::IOOracleConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IOOracleConverter::getTestMethod()
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

QJsonObject IOOracleConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Oracle)) {
        return jsonObj;
    }
    TOracle* test = qobject_cast<TOracle*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getDatabase()));
    jsonObj.insert(SP_USER, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    return jsonObj;
}

/******************************************************************/

TestMethod *IOOracleConverter::fromJsonObject(QJsonObject jsonObj)
{
    TOracle *test = qobject_cast<TOracle*>(getTestMethod());
    test->setDatabase(jsonObj.value(SP_SERVER).toString());
    test->setLogin(jsonObj.value(SP_USER).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    return test;
}

/******************************************************************/


} // namespace SDPO
