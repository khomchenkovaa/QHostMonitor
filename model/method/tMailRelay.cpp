#include "tMailRelay.h"

namespace SDPO {

TMailRelay::TMailRelay(QObject *parent) :
    TTestMethod(TMethodID::MailRelay, parent)
{
    a_Outgoing = QString("");
    a_Incoming = QString("");
    a_Sender = QString("");
}

/******************************************************************/

void TMailRelay::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TMailRelay::clone()
{
    TMailRelay *result = new TMailRelay(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Outgoing = a_Outgoing;
    result->a_Incoming = a_Incoming;
    result->a_Sender = a_Sender;
    return result;
}

/******************************************************************/

QString TMailRelay::getTestMethod() const
{
    QString s = a_Sender;
    s.replace(QRegExp("-"), "to");
    return QString("MailRelay: %1").arg(s);
}

/******************************************************************/

QString TMailRelay::getTestedObjectInfo() const
{
    QString s = a_Sender;
    s.replace(QRegExp("-"), "to");
    return QString("MailRelay: %1").arg(s);
}

/******************************************************************/

} // namespace SDPO
