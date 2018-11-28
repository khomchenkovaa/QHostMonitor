#include "ioMailRelayConverter.h"

namespace SDPO {

/***********************************************/

IOMailRelayConverter::IOMailRelayConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/***********************************************/

TTestMethod *IOMailRelayConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TMailRelay();
    }
    return m_TestMethod;
}

/***********************************************/

bool IOMailRelayConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MailRelay)) {
        return false;
    }
    TMailRelay *test = qobject_cast<TMailRelay*>(m_TestMethod);
    if (key == SP_OUTGOING) {
        test->setOutgoing(value);
    } else if (key == SP_INCOMING) {
        test->setIncoming(value);
    } else if (key == SP_SENDER) {
        test->setSender(value);
    } else {
        return false;
    }
    return true;
}

/***********************************************/

void IOMailRelayConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MailRelay)) {
        return;
    }
    TMailRelay *test = qobject_cast<TMailRelay*>(m_TestMethod);
    out << SP_OUTGOING         << " = " << test->getOutgoing()  << endl;
    out << SP_INCOMING         << " = " << test->getIncoming()  << endl;
    out << SP_SENDER           << " = " << test->getSender()    << endl;

}

/***********************************************/

QJsonObject IOMailRelayConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::MailRelay)) {
        return jsonObj;
    }
    TMailRelay* test = qobject_cast<TMailRelay*>(m_TestMethod);
    jsonObj.insert(SP_OUTGOING, QJsonValue(test->getOutgoing()));
    jsonObj.insert(SP_INCOMING, QJsonValue(test->getIncoming()));
    jsonObj.insert(SP_SENDER, QJsonValue(test->getSender()));
    return jsonObj;
}

/******************************************************************/

TTestMethod *IOMailRelayConverter::fromJsonObject(QJsonObject jsonObj)
{
    TMailRelay *test = qobject_cast<TMailRelay*>(getTestMethod());
    test->setOutgoing(jsonObj.value(SP_OUTGOING).toString());
    test->setIncoming(jsonObj.value(SP_INCOMING).toString());
    test->setSender(jsonObj.value(SP_SENDER).toString());
    return test;
}

/******************************************************************/

} // namespace SDPO

