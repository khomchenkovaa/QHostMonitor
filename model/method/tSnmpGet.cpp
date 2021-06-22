#include "tSnmpGet.h"
#include "tEnums.h"
#include "gData.h"

#include "netsnmpsession.h"

namespace SDPO {

/******************************************************************/

TSnmpGet::TSnmpGet(QObject *parent) :
    TestMethod(TMethodID::SNMP, parent)
{
    a_Host = "localhost";
    a_SnmpProfile = "public v2";
    a_Timeout = 2;
    a_Retries = 1;
    a_MibOid = ".1.3.6.1.2.1.1.3.0";
    a_Condition = Condition::Contain;
    a_Version = "v2c";
}

/******************************************************************/

void TSnmpGet::run()
{
    m_Result.clear();

    SnmpProfile profile = SnmpProfile::findByName(a_SnmpProfile);

    NetSnmpSession ss;
    ss.setProfile(profile);
    ss.setRetries(a_Retries);
    ss.setDestHost(a_Host);
    SnmpValue value = ss.get(a_MibOid);
    if (value.type != SnmpDataUnknown) {
        parseResult(value.val);
        emit testSuccess();
    } else {
        emit testFailed();
    }
}

/******************************************************************/

void TSnmpGet::parseResult(QString data)
{
    TestResult result;
    result.reply = data;

    bool isFloat = true;
    double replyDouble = data.toDouble(&isFloat);
    double oldDouble = m_Result.reply.toDouble();
    double valueAsFloat = isFloat? a_Value.toDouble(&isFloat) : 0.0;
    bool isInt = true;
    int replyInt = data.toInt(&isInt);
    int oldInt = m_Result.reply.toInt();
    int valueAsInt = isInt? a_Value.toInt(&isInt) : 0;

    switch (a_Condition) {
    case Condition::LessThan:
        if (isFloat) {
            result.status = (replyDouble < valueAsFloat)? TestStatus::Bad : TestStatus::Ok;
        } else if (isInt) {
            result.status = (replyInt < valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        } else {
            result.status = (result.reply.toString().compare(a_Value) < 0)? TestStatus::Bad : TestStatus::Ok;
        }
        break;
    case Condition::MoreThan:
        if (isFloat) {
            result.status = (replyDouble > valueAsFloat)? TestStatus::Bad : TestStatus::Ok;
        } else if (isInt) {
            result.status = (replyInt > valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        } else {
            result.status = (result.reply.toString().compare(a_Value) > 0)? TestStatus::Bad : TestStatus::Ok;
        }
        break;
    case Condition::EqualTo:
        result.status = (result.reply.toString().compare(a_Value) == 0)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::DifferentFrom:
        result.status = (result.reply.toString().compare(a_Value) != 0)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::Contain:
        result.status = (result.reply.toString().contains(a_Value))? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::NotContain:
        result.status = (!result.reply.toString().contains(a_Value))? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::IncreaseBy:
        result.status = (replyInt + valueAsInt >= oldInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::DecreaseBy:
        result.status = (replyInt + valueAsInt <= oldInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::ChangeBy:
        result.status = (qAbs(replyInt-oldInt) >= valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::IncByPercent:
        result.status = (100*(replyInt-oldInt)/oldInt >= valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::DecByPercent:
        result.status = (100*(replyInt-oldInt)/oldInt <= valueAsInt)? TestStatus::Bad : TestStatus::Ok;
        break;
    case Condition::ChangeByPercent:
        result.status = (100*qAbs(replyInt-oldInt)/oldInt >= valueAsInt)? TestStatus::Bad : TestStatus::Ok;
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
    m_Result = result;
}

/******************************************************************/

TestMethod *TSnmpGet::clone()
{
    TSnmpGet *result = new TSnmpGet(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Host = a_Host;
    result->a_SnmpProfile = a_SnmpProfile;
    result->a_Condition = a_Condition;
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
    return QString("SNMP Get %1 from %2").arg(a_MibName, a_Host);
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
    return static_cast<TSnmpGet::Condition>(idx);
}

/******************************************************************/

} // namespace SDPO
