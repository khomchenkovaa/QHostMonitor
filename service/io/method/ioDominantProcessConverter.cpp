#include "ioDominantProcessConverter.h"

namespace SDPO {

/******************************************************************/

IODominantProcessConverter::IODominantProcessConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IODominantProcessConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TDominantProcess();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IODominantProcessConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DominantProcess)) {
        return false;
    }
    TDominantProcess *test = qobject_cast<TDominantProcess*>(m_TestMethod);
    if (key == SP_CHECKPROCESSON) {
        test->setCheckProcessesOn(value);
    } else if (key == SP_EXCLUDEPROCESSES) {
        test->setExcludeProcesses(value);
    } else if (key == SP_ALERTIFCOUNT) {
        test->setAlertIfCount(value.toInt());
    } else if (key == SP_ALERTIF) {
        test->setAlertIf(value);
    } else if (key == SP_TOPPROCESSES) {
        test->setTopProcesses(value);
    } else if (key == SP_LOGIN) {
        test->setLogin(value);
        test->setConnectAs(true);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IODominantProcessConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DominantProcess)) {
        return;
    }
    TDominantProcess*test = qobject_cast<TDominantProcess*>(m_TestMethod);
    out << SP_CHECKPROCESSON      << " = " << test->getCheckProcessesOn()    << endl;
    out << SP_EXCLUDEPROCESSES    << " = " << test->getExcludeProcesses()    << endl;
    out << SP_ALERTIFCOUNT        << " = " << test->getAlertIfCount()        << endl;
    out << SP_ALERTIF             << " = " << test->getAlertIf()             << endl;
    out << SP_TOPPROCESSES        << " = " << test->getTopProcesses()        << endl;
    if (test->isConnectAs()) {
        out << SP_LOGIN      << " = " << test->getLogin()                    << endl;
        out << SP_PASSWORD   << " = " << test->getPassword()                 << endl;
    }
}
/******************************************************************/

QJsonObject IODominantProcessConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DominantProcess)) {
        return jsonObj;
    }
    TDominantProcess* test = qobject_cast<TDominantProcess*>(m_TestMethod);
    jsonObj.insert(SP_CHECKPROCESSON, QJsonValue(test->getCheckProcessesOn()));
    jsonObj.insert(SP_EXCLUDEPROCESSES, QJsonValue(test->getExcludeProcesses()));
    jsonObj.insert(SP_ALERTIFCOUNT, QJsonValue(test->getAlertIfCount()));
    jsonObj.insert(SP_ALERTIF, QJsonValue(test->getAlertIf()));
    jsonObj.insert(SP_TOPPROCESSES, QJsonValue(test->getTopProcesses()));
    if (test->isConnectAs()) {
        jsonObj.insert(SP_LOGIN, QJsonValue(test->getLogin()));
        jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    }
    return jsonObj;
}

/******************************************************************/

TestMethod *IODominantProcessConverter::fromJsonObject(QJsonObject jsonObj)
{
    TDominantProcess *test = qobject_cast<TDominantProcess*>(getTestMethod());
    test->setCheckProcessesOn(jsonObj.value(SP_CHECKPROCESSON).toString());
    test->setExcludeProcesses(jsonObj.value(SP_EXCLUDEPROCESSES).toString());
    test->setAlertIfCount(jsonObj.value(SP_ALERTIFCOUNT).toInt());
    test->setAlertIf(jsonObj.value(SP_ALERTIF).toString());
    test->setTopProcesses(jsonObj.value(SP_TOPPROCESSES).toString());
    if (test->isConnectAs()){
        test->setLogin(jsonObj.value(SP_LOGIN).toString());
        test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    }
    return test;
}

/******************************************************************/

} //namespace SDPO
