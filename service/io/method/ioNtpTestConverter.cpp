#include "ioNtpTestConverter.h"

namespace SDPO {

/******************************************************************/

IONtpTestConverter::IONtpTestConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}


/******************************************************************/

TestMethod *IONtpTestConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TNtpTest();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IONtpTestConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::NTP)) {
        return false;
    }
    TNtpTest *test = qobject_cast<TNtpTest*>(m_TestMethod);
    if (key == SP_SERVER) {
        test->setServer(value);
    } else if (key == SP_PORT) {
        test->setPort(value.toInt());
    } else if (key == SP_RETRIES) {
        test->setRetries(value.toInt());
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_ALERTWHEN) {
        test->setAlertWhen(value == "Yes");
    } else if (key == SP_SEC) {
        test->setSec(value.toInt());
    } else if (key == SP_DISPLAYMODE) {
        test->setDisplayMode(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IONtpTestConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::NTP)) {
        return;
    }
    TNtpTest*test = qobject_cast<TNtpTest*>(m_TestMethod);
    out << SP_SERVER        << " = " << test->getServer()         << endl;
    out << SP_PORT          << " = " << test->getPort()           << endl;
    out << SP_RETRIES       << " = " << test->getRetries()        << endl;
    out << SP_TIMEOUT       << " = " << test->getTimeout()        << endl;
    out << SP_ALERTWHEN     << " = " << test->isAlertWhen()       << endl;
    out << SP_SEC           << " = " << test->getSec()            << endl;
    out << SP_DISPLAYMODE   << " = " << test->getDisplayMode()    << endl;

}
/******************************************************************/

QJsonObject IONtpTestConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::NTP)) {
        return jsonObj;
    }
    TNtpTest* test = qobject_cast<TNtpTest*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getServer()));
    jsonObj.insert(SP_PORT, QJsonValue(test->getPort()));
    jsonObj.insert(SP_RETRIES, QJsonValue(test->getRetries()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_ALERTWHEN, QJsonValue(test->isAlertWhen()));
    jsonObj.insert(SP_SEC, QJsonValue(test->getSec()));
    jsonObj.insert(SP_DISPLAYMODE, QJsonValue(test->getDisplayMode()));
    return jsonObj;
}

/******************************************************************/

TestMethod *IONtpTestConverter::fromJsonObject(QJsonObject jsonObj)
{
    TNtpTest *test = qobject_cast<TNtpTest*>(getTestMethod());
    test->setServer(jsonObj.value(SP_SERVER).toString());
    test->setPort(jsonObj.value(SP_PORT).toInt());
    test->setRetries(jsonObj.value(SP_RETRIES).toInt());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setAlertWhen(jsonObj.value(SP_ALERTWHEN).toBool());
    test->setSec(jsonObj.value(SP_SEC).toInt());
    test->setDisplayMode(jsonObj.value(SP_DISPLAYMODE).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO
