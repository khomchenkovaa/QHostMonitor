#include "ioIMAPTestConverter.h"

namespace SDPO {

/******************************************************************/

IOIMAPTestConverter::IOIMAPTestConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/******************************************************************/

TTestMethod *IOIMAPTestConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TImapTest();
    }
    return m_TestMethod;
}

/******************************************************************/

bool IOIMAPTestConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::IMAP)) {
        return false;
    }
    TImapTest *test = qobject_cast<TImapTest*>(m_TestMethod);
    if (key == SP_SERVER) {
        test->setServer(value);
    } else if (key == SP_PORT) {
        test->setPort(value.toInt());
    } else if (key == SP_LOGIN) {
        test->setLogin(value);
    } else if (key == SP_TLS) {
        test->setTls(value);
    } else if (key == SP_PASSWORD) {
        test->setPassword(value);
    } else if (key == SP_TIMEOUT) {
        test->setTimeout(value.toInt());
    } else if (key == SP_CHECKMAILBOX) {
        test->setCheckMailbox(value == "Yes");
    } else if (key == SP_MESSAGEFOLDER) {
        test->setMessageFolder(value);
    } else if (key == SP_MESSAGESTATUS) {
        test->setMessageStatus(value);
    } else if (key == SP_MESSAGEALERT) {
        test->setMessageAlert(value);
    } else if (key == SP_MESSAGESIZE) {
        test->setMessageSize(value.toInt());
    } else {
        return false;
    }
    return true;
}

/******************************************************************/

void IOIMAPTestConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::IMAP)) {
        return;
    }
    TImapTest*test = qobject_cast<TImapTest*>(m_TestMethod);
    out << SP_SERVER           << " = " << test->getServer()           << endl;
    out << SP_PORT             << " = " << test->getPort()             << endl;
    out << SP_LOGIN            << " = " << test->getLogin()            << endl;
    out << SP_TLS              << " = " << test->getTls()              << endl;
    out << SP_PASSWORD         << " = " << test->getPassword()         << endl;
    out << SP_TIMEOUT          << " = " << test->getTimeout()          << endl;
    out << SP_CHECKMAILBOX     << " = " << test->isCheckMailbox()      << endl;
    out << SP_MESSAGEFOLDER    << " = " << test->getMessageFolder()    << endl;
    out << SP_MESSAGESTATUS    << " = " << test->getMessageStatus()    << endl;
    out << SP_MESSAGEALERT     << " = " << test->getMessageAlert()     << endl;
    out << SP_MESSAGESIZE      << " = " << test->getMessageSize()      << endl;
}

/******************************************************************/

QJsonObject IOIMAPTestConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::IMAP)) {
        return jsonObj;
    }
    TImapTest* test = qobject_cast<TImapTest*>(m_TestMethod);
    jsonObj.insert(SP_SERVER, QJsonValue(test->getServer()));
    jsonObj.insert(SP_PORT, QJsonValue(test->getPort()));
    jsonObj.insert(SP_LOGIN, QJsonValue(test->getLogin()));
    jsonObj.insert(SP_TLS, QJsonValue(test->getTls()));
    jsonObj.insert(SP_PASSWORD, QJsonValue(test->getPassword()));
    jsonObj.insert(SP_TIMEOUT, QJsonValue(test->getTimeout()));
    jsonObj.insert(SP_CHECKMAILBOX, QJsonValue(test->isCheckMailbox()));
    jsonObj.insert(SP_MESSAGEFOLDER, QJsonValue(test->getMessageFolder()));
    jsonObj.insert(SP_MESSAGESTATUS, QJsonValue(test->getMessageFolder()));
    jsonObj.insert(SP_MESSAGEALERT, QJsonValue(test->getMessageAlert()));
    jsonObj.insert(SP_MESSAGESIZE, QJsonValue(test->getMessageSize()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOIMAPTestConverter::fromJsonObject(QJsonObject jsonObj)
{
    TImapTest *test = qobject_cast<TImapTest*>(getTestMethod());
    test->setServer(jsonObj.value(SP_SERVER).toString());
    test->setPort(jsonObj.value(SP_PORT).toInt());
    test->setLogin(jsonObj.value(SP_LOGIN).toString());
    test->setTls(jsonObj.value(SP_TLS).toString());
    test->setPassword(jsonObj.value(SP_PASSWORD).toString());
    test->setTimeout(jsonObj.value(SP_TIMEOUT).toInt());
    test->setCheckMailbox(jsonObj.value(SP_CHECKMAILBOX).toBool());
    test->setMessageFolder(jsonObj.value(SP_MESSAGEFOLDER).toString());
    test->setMessageStatus(jsonObj.value(SP_MESSAGESTATUS).toString());
    test->setMessageAlert(jsonObj.value(SP_MESSAGEALERT).toString());
    test->setMessageSize(jsonObj.value(SP_MESSAGESIZE).toInt());
    return test;
}

/******************************************************************/

} //namespace SDPO
