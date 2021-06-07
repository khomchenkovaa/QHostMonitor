#include "ioNtEventLogConverter.h"

namespace SDPO {


/******************************************************************/

IONtEventLogConverter::IONtEventLogConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TestMethod *IONtEventLogConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TNtEventLog();
    }
    return m_TestMethod;
}
/******************************************************************/

bool IONtEventLogConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::NTLog)) {
        return false;
    }
    TNtEventLog *test = qobject_cast<TNtEventLog*>(m_TestMethod);
    if (key == SP_LOGSOURCE) {
        test->setLogSource(value == "Yes");
    } else if (key == SP_ALERTCONDITION) {
        test->setAlertCondition(value == "Yes");
    } else if (key == SP_CONNECTAS) {
        test->setConnectAs(value == "Yes");
    } else if (key == SP_COMPABILITY) {
        test->setCompatibility(value);
    } else if (key == SP_COMPUTERUNC) {
        test->setComputerUnc(value);
    } else if (key == SP_LOG) {
        test->setLog(value);
    } else if (key == SP_EVENTSOURCE) {
        test->setEventSource(value);
    } else if (key == SP_COMPUTER) {
        test->setComputer(value);
    } else if (key == SP_EVENTTYPE) {
        test->setEventType(value);
    } else if (key == SP_EVENTID) {
        test->setEventId(value);
    } else if (key == SP_DESCRIPTION) {
        test->setDescription(value);
    } else if (key == SP_CONNECTTOREMOTE) {
        test->setConnectToRemote(value == "Yes");
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

void IONtEventLogConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::NTLog)) {
        return;
    }
    TNtEventLog *test = qobject_cast<TNtEventLog*>(m_TestMethod);
    out << SP_LOGSOURCE         << " = " << test->isLogSource()          << endl;
    out << SP_ALERTCONDITION    << " = " << test->isAlertCondition()     << endl;
    out << SP_CONNECTAS         << " = " << test->isConnectAs()          << endl;
    out << SP_COMPABILITY       << " = " << test->getCompatibility()     << endl;
    out << SP_COMPUTERUNC       << " = " << test->getComputerUnc()       << endl;
    out << SP_LOG               << " = " << test->getLog()               << endl;
    out << SP_EVENTSOURCE       << " = " << test->getEventSource()       << endl;
    out << SP_COMPUTER          << " = " << test->getComputer()          << endl;
    out << SP_EVENTTYPE         << " = " << test->getEventType()         << endl;
    out << SP_EVENTID           << " = " << test->getEventId()           << endl;
    out << SP_DESCRIPTION       << " = " << test->getDescription()       << endl;
    out << SP_CONNECTTOREMOTE   << " = " << test->isConnectToRemote()    << endl;
    out << SP_LOGIN             << " = " << test->getLogin()             << endl;
    out << SP_PASSWORD          << " = " << test->getPassword()          << endl;
}
/******************************************************************/

QJsonObject IONtEventLogConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::NTLog)) {
        return jsonObj;
    }
    TNtEventLog* test = qobject_cast<TNtEventLog*>(m_TestMethod);
    jsonObj.insert(SP_LOGSOURCE, QJsonValue(test->isLogSource()));
    jsonObj.insert(SP_ALERTCONDITION, QJsonValue(test->isAlertCondition()));
    jsonObj.insert(SP_CONNECTAS, QJsonValue(test->isConnectAs()));
    jsonObj.insert(SP_COMPABILITY, QJsonValue(test->getCompatibility()));
    jsonObj.insert(SP_COMPUTERUNC, QJsonValue(test->getComputerUnc()));
    jsonObj.insert(SP_LOG, QJsonValue(test->getLog()));
    jsonObj.insert(SP_EVENTSOURCE, QJsonValue(test->getCompatibility()));
    jsonObj.insert(SP_COMPUTER, QJsonValue(test->getComputerUnc()));
    jsonObj.insert(SP_EVENTTYPE, QJsonValue(test->getLog()));
    jsonObj.insert(SP_EVENTID, QJsonValue(test->getCompatibility()));
    jsonObj.insert(SP_DESCRIPTION, QJsonValue(test->getComputerUnc()));
    jsonObj.insert(SP_CONNECTTOREMOTE, QJsonValue(test->isConnectToRemote()));
    jsonObj.insert(SP_LOGIN, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    return jsonObj;
}

/******************************************************************/

TestMethod *IONtEventLogConverter::fromJsonObject(QJsonObject jsonObj)
{
    TNtEventLog *test = qobject_cast<TNtEventLog*>(getTestMethod());
    test->setLogSource(jsonObj.value(SP_LOGSOURCE).toBool());
    test->setAlertCondition(jsonObj.value(SP_ALERTCONDITION).toBool());
    test->setConnectAs(jsonObj.value(SP_CONNECTAS).toBool());
    test->setCompatibility(jsonObj.value(SP_COMPABILITY).toString());
    test->setComputerUnc(jsonObj.value(SP_COMPUTERUNC).toString());
    test->setLog(jsonObj.value(SP_LOG).toString());
    test->setEventSource(jsonObj.value(SP_EVENTSOURCE).toString());
    test->setComputer(jsonObj.value(SP_COMPUTER).toString());
    test->setEventType(jsonObj.value(SP_EVENTTYPE).toString());
    test->setEventId(jsonObj.value(SP_EVENTID).toString());
    test->setDescription(jsonObj.value(SP_DESCRIPTION).toString());
    test->setConnectToRemote(jsonObj.value(SP_CONNECTTOREMOTE).toBool());
    test->setLogin(jsonObj.value(SP_LOGIN).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    return test;
}

/******************************************************************/

} //namespace SDPO


