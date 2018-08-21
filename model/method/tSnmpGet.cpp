#include "tSnmpGet.h"
#include "tEnums.h"
#include <QProcess>

namespace SDPO {

/******************************************************************/

TSnmpGet::TSnmpGet(QObject *parent) :
    TTestMethod(TMethodID::SNMP, parent)
{
    a_Host = "localhost";
    a_Community = "public";
    a_Timeout = 2;
    a_Retries = 1;
    a_MibOid = ".1.3.6.1.2.1.1.3.0";
    a_Condition = Condition::Contain;
    a_Version = "v2c";
}

/******************************************************************/

void TSnmpGet::run()
{
    clearResult();

    QString command = getCommand();
    if (command.isEmpty()) {
        m_ErrorString = "Command is empty";
        emit testFailed();
        return;
    }

//    qDebug() << getTestMethod() << ":" << command;

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        m_Reply = getTestedObjectInfo() + " can not start";
        process.close();
        emit testFailed();
        return;
    }
    if(!process.waitForFinished()) {
        m_Reply = getTestedObjectInfo() + " terminated";
        process.close();
        emit testFailed();
        return;
    }
    if( process.exitStatus() == QProcess::NormalExit ) {
        parseResult(process.readAll().trimmed());
        emit testSuccess();
    } else {
        m_ErrorString = process.errorString();
        emit testFailed();
    }
}

/******************************************************************/

QString TSnmpGet::getCommand() const
{
    QString cmd = "snmpget -m ALL ";
    cmd += QString("-%1 ").arg(a_Version);
    cmd += QString("-c %1 ").arg(a_Community);
    cmd += QString("-t %1 ").arg(a_Timeout);
    cmd += QString("-r %1 ").arg(a_Retries);
    cmd += a_Host + " ";
    cmd += a_MibOid;
    return cmd;
}

/******************************************************************/

void TSnmpGet::parseResult(QString data)
{
    QString oidName = data.trimmed();
    QString newReply = data.trimmed();
//    qDebug() << "SNMP Get data:" << data;
    int idx = data.indexOf(" = ");
    if (idx != -1) {
        oidName.truncate(idx);
        a_OidFullName = oidName;
        if (oidName.endsWith(".0")) {
            oidName.truncate(oidName.length()-2);
        }
        int lastDotIdx = oidName.lastIndexOf(".");
        int dotDotIdx = oidName.lastIndexOf("::");
        if (lastDotIdx > dotDotIdx) {
            a_MibName = oidName.mid(lastDotIdx+1);
        } else if (dotDotIdx >= 0) {
            a_MibName = oidName.mid(dotDotIdx+2);
        } else {
            a_MibName = oidName;
        }
        newReply = newReply.mid(idx + 3);
        newReply = newReply.mid(newReply.indexOf(": ") + 2);
    }

    bool isFloat = true;
    float newReplyFloat = data.toFloat(&isFloat);
    float valueAsFloat = isFloat? a_Value.toFloat(&isFloat) : 0.0;
    bool isInt = true;
    int newReplyInt = data.toInt(&isInt);
    int valueAsInt = isInt? a_Value.toInt(&isInt) : 0;
//    qDebug() << "Float:" << newReplyFloat << "Int:" << newReplyInt;
    TestStatus newStatus = TestStatus::Unknown;

    switch (a_Condition) {
    case Condition::LessThan:
        if (isFloat) {
            newStatus = (newReplyFloat < valueAsFloat)? TestStatus::Bad : TestStatus::Ok;
        } else if (isInt) {
            newStatus = (newReplyInt < valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        } else {
            newStatus = (newReply.compare(a_Value) < 0)? TestStatus::Bad : TestStatus::Ok;
        }
        break;
    case Condition::MoreThan:
        if (isFloat) {
            newStatus = (newReplyFloat > valueAsFloat)? TestStatus::Bad : TestStatus::Ok;
        } else if (isInt) {
            newStatus = (newReplyInt > valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        } else {
            newStatus = (newReply.compare(a_Value) > 0)? TestStatus::Bad : TestStatus::Ok;
        }
        break;
    case Condition::EqualTo:
        newStatus = (newReply.compare(a_Value) == 0)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::DifferentFrom:
        newStatus = (newReply.compare(a_Value) != 0)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::Contain:
        newStatus = (newReply.contains(a_Value))? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::NotContain:
        newStatus = (!newReply.contains(a_Value))? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::IncreaseBy:
        newStatus = (newReplyInt + valueAsInt >= getReplyInt())? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::DecreaseBy:
        newStatus = (newReplyInt + valueAsInt <= getReplyInt())? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::ChangeBy:
        newStatus = (qAbs(newReplyInt-getReplyInt()) >= valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::IncByPercent:
        newStatus = (100*(newReplyInt-getReplyInt())/getReplyInt() >= valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::DecByPercent:
        newStatus = (100*(newReplyInt-getReplyInt())/getReplyInt() <= valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::ChangeByPercent:
        newStatus = (100*qAbs(newReplyInt-getReplyInt())/getReplyInt() >= valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::IncSec:
        // TODO "Bad" status when average increase of the counter (per second) is greater than the specified limit
        // (new value - old value)/elapsed time >= specified limit
        break;
    case Condition::DecSec:
        // TODO "Bad" status when average decrease of the counter (per second) is greater than the specified limit
        // (old value - new value)/elapsed time >= specified limit
        break;
    case Condition::ChangeSec:
        // TODO "Bad" status when average change of the counter (per second) is greater than the specified limit
        // abs(new value - old value)/elapsed time >= specified limit
        break;
    }
    m_Status = newStatus;
    m_Reply = newReply;
    m_ReplyDouble = newReplyFloat;
    m_ReplyInt = newReplyInt;
}

/******************************************************************/

TTestMethod *TSnmpGet::clone()
{
    TSnmpGet *result = new TSnmpGet(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_Host = a_Host;
    result->a_Community = a_Community;
    result->a_MibOid = a_MibOid;
    result->a_MibName = a_MibName;
    result->a_OidFullName = a_OidFullName;
    result->a_Timeout = a_Timeout;
    result->a_Retries = a_Retries;
    result->a_Value = a_Value;
    result->a_Version = a_Version;
    return result;
}

/******************************************************************/

QString TSnmpGet::getTestMethod() const
{
    return QString("SNMP test");
}

/******************************************************************/

QString TSnmpGet::getTestedObjectInfo() const
{
    return QString("SNMP Get %1 from %2").arg(a_MibName).arg(a_Host);
}

/******************************************************************/

const static QStringList conditionStr = QString(
      "LessThan,MoreThan,EqualTo,DifferentFrom,Contain,NotContain,IncreaseBy,DecreaseBy,ChangeBy,IncreaseBy%,DecreaseBy%,ChangeBy%,IncreaseSec,DecreaseSec,ChangeSec"
            ).split(",");

/******************************************************************/

QString TSnmpGet::conditionToString(TSnmpGet::Condition cond) const
{
    return conditionStr.at(cond);
}

/******************************************************************/

TSnmpGet::Condition TSnmpGet::conditionFromString(QString condStr, Condition condDefault) const
{
    int idx = conditionStr.indexOf(condStr);
    if (idx == -1) {
        return condDefault;
    }
    return (TSnmpGet::Condition)idx;
}

/******************************************************************/

} // namespace SDPO
