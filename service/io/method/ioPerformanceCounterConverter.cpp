#include "ioPerformanceCounterConverter.h"

namespace SDPO {

/******************************************************************/

IOPerformanceCounterConverter::IOPerformanceCounterConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IOPerformanceCounterConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TPerformanceCounter();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IOPerformanceCounterConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::PerfCounter)) {
        return false;
    }
    TPerformanceCounter *test = qobject_cast<TPerformanceCounter*>(m_TestMethod);
    if (key == SP_CHECKCOUNTER) {
        test->setCheckCounter(value);
    } else if (key == SP_ALERTWHEN) {
        test->setAlertWhen(value);
    } else if (key == SP_ALERTWHENCOUNTER) {
        test->setAlertWhenCounter(value.toInt());
    } else if (key == SP_DISPLAYMODE) {
        test->setDisplayMode(value);
    } else if (key == SP_LOGIN) {
        test->setAlertWhen(value);
        test->setConnectAs(true);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOPerformanceCounterConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::PerfCounter)) {
        return;
    }
    TPerformanceCounter *test = qobject_cast<TPerformanceCounter*>(m_TestMethod);
    out << SP_CHECKCOUNTER      << " = " << test->getCheckCounter()     << endl;
    out << SP_ALERTWHEN         << " = " << test->getAlertWhen()        << endl;
    out << SP_ALERTWHENCOUNTER  << " = " << test->getAlertWhenCounter() << endl;
    out << SP_DISPLAYMODE       << " = " << test->getDisplayMode()      << endl;
    if (test->isConnectAs()) {
        out << SP_LOGIN     << " = " << test->getLogin()    << endl;
        out << SP_PASSWORD  << " = " << test->getPassword() << endl;
    }

}
/******************************************************************/

QJsonObject IOPerformanceCounterConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::PerfCounter)) {
        return jsonObj;
    }
    TPerformanceCounter* test = qobject_cast<TPerformanceCounter*>(m_TestMethod);
    jsonObj.insert(SP_CHECKCOUNTER, QJsonValue(test->getCheckCounter()));
    jsonObj.insert(SP_ALERTWHEN, QJsonValue(test->getAlertWhen()));
    jsonObj.insert(SP_ALERTWHENCOUNTER, QJsonValue(test->getAlertWhenCounter()));
    jsonObj.insert(SP_DISPLAYMODE, QJsonValue(test->getDisplayMode()));
    if (test->isConnectAs()) {
    jsonObj.insert(SP_LOGIN, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    }
    return jsonObj;
}

/******************************************************************/

TestMethod *IOPerformanceCounterConverter::fromJsonObject(QJsonObject jsonObj)
{
    TPerformanceCounter *test = qobject_cast<TPerformanceCounter*>(getTestMethod());
    test->setCheckCounter(jsonObj.value(SP_CHECKCOUNTER).toString());
    test->setAlertWhen(jsonObj.value(SP_ALERTWHEN).toString());
    test->setAlertWhenCounter(jsonObj.value(SP_ALERTWHENCOUNTER).toInt());
    test->setDisplayMode(jsonObj.value(SP_DISPLAYMODE).toString());
    if (test->isConnectAs()) {
    test->setLogin(jsonObj.value(SP_LOGIN).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    }
    return test;
}

/******************************************************************/


} // namespace SDPO

