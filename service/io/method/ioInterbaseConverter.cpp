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

QJsonObject IOInterbaseConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::Interbase)) {
        return jsonObj;
    }
    TInterbase* test = qobject_cast<TInterbase*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getHost()));
    jsonObj.insert(SP_DATABASE, QJsonValue(test->getDatabase()));
    jsonObj.insert(SP_USER, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    jsonObj.insert(SP_PROTOCOL, QJsonValue(test->getProtocol()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOInterbaseConverter::fromJsonObject(QJsonObject jsonObj)
{
    TInterbase *test = qobject_cast<TInterbase*>(getTestMethod());
    test->setHost(jsonObj.value(SP_SERVER).toString());
    test->setDatabase(jsonObj.value(SP_DATABASE).toString());
    test->setLogin(jsonObj.value(SP_USER).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    test->setProtocol(jsonObj.value(SP_PROTOCOL).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO
