#include "ioActionProfileLoader.h"
#include "gData.h"
#include "action/tWinPopupAction.h"
#include "action/tPlaySoundAction.h"
#include "action/tSendMessageToPagerTapAction.h"
#include "action/tSendMessageToPagerSnppAction.h"
#include "action/tSendMessageToBeeperAction.h"
#include "action/tSendSmsGsmModemAction.h"
#include "action/tSendSmsSmppAction.h"
#include "action/tSendEmailSmtpAction.h"
#include "action/tSendMessageToIcqAction.h"
#include "action/tSendMessageToJabberAction.h"
#include "action/tRecordSdpoLogAction.h"
#include "action/tGenerateReportsAction.h"
#include "action/tStopServiceAction.h"
#include "action/tStartServiceAction.h"
#include "action/tRestartServiceAction.h"
#include "action/tRebootRemoteSystemAction.h"
#include "action/tRebootLocalMachineAction.h"
#include "action/tDialupToTheNetworkAction.h"
#include "action/tDisconnectDialupConnectionAction.h"
#include "action/tExecuteExternalProgramAction.h"
#include "action/tLogEventAction.h"
#include "action/tSqlQueryAction.h"
#include "action/tHttpRequestAction.h"
#include "action/tSendDataToTcpUdpPortAction.h"
#include "action/tSyslogAction.h"
#include "action/tSnmpSetAction.h"
#include "action/tSnmpTrapAction.h"
#include "action/tRepeatTestAction.h"
#include "action/tChangeTestIntervalAction.h"
#include "action/tRunHmsScriptAction.h"

namespace SDPO {

/*****************************************************************/

IOActionProfileLoader::IOActionProfileLoader(QObject *parent) :
    IODataLoader("actions.json", parent)
{
}

/*****************************************************************/

void IOActionProfileLoader::load()
{
    GData::actionProfiles.clear();
    QString rawJson = readJsonFile();
    if (rawJson.size() == 0) return;

    QPair<QJsonDocument, QJsonParseError> jsonResult = getJsonDocument(rawJson);
    QJsonParseError jsonError = jsonResult.second;
    if (jsonError.error != QJsonParseError::NoError) {
        QString msg = tr("Error parsing JSON actions file at %1: %2").arg(jsonError.offset).arg(jsonError.errorString());
        sendErrorMessage(msg);
        return;
    }
    QJsonDocument jsonDoc = jsonResult.first;
    parseJsonData(jsonDoc);
}

/*****************************************************************/

void IOActionProfileLoader::save()
{
    QJsonDocument jsonDocument = createJsonDocument();
    writeJsonToStdConfigFile(QString(jsonDocument.toJson()));
}

/*****************************************************************/

void IOActionProfileLoader::parseJsonData(QJsonDocument json_doc)
{
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &item, json_array) {
        QJsonObject json_obj = item.toObject();
        GActionProfile profile;
        profile.name = json_obj["name"].toString();
        QJsonArray onBad_array = json_obj["onBad"].toArray();
        foreach (const QJsonValue &obj, onBad_array) {
            profile.onBad << parseAction(obj.toObject());
        }
        QJsonArray onGood_array = json_obj["onGood"].toArray();
        foreach (const QJsonValue &obj, onGood_array) {
            profile.onGood << parseAction(obj.toObject());
        }
        QJsonArray comments_array = json_obj["comment"].toArray();
        foreach (const QJsonValue &line, comments_array) {
            profile.comments << line.toString();
        }

        GData::actionProfiles.append(profile);
    }
}

/*****************************************************************/

TestAction *IOActionProfileLoader::parseAction(QJsonObject json_obj)
{
    TestAction *result;
    QString action = json_obj["action"].toString();
    TActionID id = TAction::fromCode(action);
    switch (id) {
    case TActionID::WinPopup:
        result = new WinPopupAction();
        break;
    case TActionID::PlaySound: {
        PlaySoundAction *playSound = new PlaySoundAction();
        playSound->setFile(json_obj["file"].toString());
        playSound->setWakeUp(json_obj["wakeUp"].toBool());
        result = playSound;
        } break;
    case TActionID::MsgPagerTap: {
        SendMessageToPagerTapAction *msgPagerTap = new SendMessageToPagerTapAction();
        msgPagerTap->setAccessNumber(json_obj["accessNumber"].toString());
        msgPagerTap->setPassword(json_obj["password"].toString());
        msgPagerTap->setMaxCharacter(json_obj["maxCharacter"].toInt());
        msgPagerTap->setParity(json_obj["parity"].toString());
        msgPagerTap->setPagerId(json_obj["pagerId"].toString());
        msgPagerTap->setMsgTemplate(json_obj["msgTemplate"].toString());
        result = msgPagerTap;
        } break;
    case TActionID::MsgPagerSnpp: {
        SendMessageToPagerSnppAction *msgPagerSnpp = new SendMessageToPagerSnppAction();
        msgPagerSnpp->setPagerID(json_obj["pajerID"].toString());
        msgPagerSnpp->setMailTemplate(json_obj["mailTemplate"].toString());
        msgPagerSnpp->setLevel(json_obj["level"].toString());
        msgPagerSnpp->setAlert(json_obj["alert"].toBool());
        msgPagerSnpp->setServer(json_obj["server"].toString());
        msgPagerSnpp->setPort(json_obj["port"].toInt());
        msgPagerSnpp->setLoginAs(json_obj["loginAs"].toBool());
        msgPagerSnpp->setLoginAsLogin(json_obj["loginAsLogin"].toString());
        msgPagerSnpp->setLoginAsPassword(json_obj["loginAsPassword"].toString());
        result = msgPagerSnpp;
        } break;
    case TActionID::MsgBeeper: {
        SendMessageToBeeperAction *MsgBeeper = new SendMessageToBeeperAction();
        MsgBeeper->setBeeper(json_obj["beeper"].toString());
        MsgBeeper->setDelay(json_obj["delay"].toInt());
        MsgBeeper->setSendMessage(json_obj["sendMessage"].toString());
        MsgBeeper->setTerminationString(json_obj["terminationString"].toString());
        result = MsgBeeper;
        } break;
    case TActionID::MsgSmsGsm: {
        SendSmsGsmModemAction *MsgSmsGsm = new SendSmsGsmModemAction();
        MsgSmsGsm->setDestPhone(json_obj["destPhone"].toString());
        MsgSmsGsm->setMsgClass(json_obj["msgClass"].toString());
        MsgSmsGsm->setMsgTemplate(json_obj["msgTemplate"].toString());
        result = MsgSmsGsm;
        } break;
    case TActionID::MsgSmsSmpp: {
        SendSmsSmppAction *MsgSmsSmpp = new SendSmsSmppAction();
        MsgSmsSmpp->setDestPhone(json_obj["destPhone"].toString());
        MsgSmsSmpp->setDestTon(json_obj["destTon"].toString());
        MsgSmsSmpp->setDestNpi(json_obj["destNpi"].toString());
        MsgSmsSmpp->setMsgTemplate(json_obj["msgTemplate"].toString());
        result = MsgSmsSmpp;
        } break;
    case TActionID::MsgEmail: {
        SendEmailSmtpAction *MsgEmail = new SendEmailSmtpAction();
        MsgEmail->setFromSender(json_obj["fromSender"].toString());
        MsgEmail->setToRecipients(json_obj["toRecipient"].toString());
        MsgEmail->setPriority(json_obj["priority"].toString());
        MsgEmail->setSubject(json_obj["subject"].toString());
        MsgEmail->setBodyTemplate(json_obj["bodyTemplate"].toString());
        MsgEmail->setAttachFile(json_obj["attachFile"].toBool());
        MsgEmail->setAttachFileSelect(json_obj["attachFileSelect"].toString());
        result = MsgEmail;
        } break;
    case TActionID::MsgIcq: {
        SendMessageToIcqAction *MsgIcq = new SendMessageToIcqAction();
        MsgIcq->setSendMessage(json_obj["sendMessage"].toString());
        MsgIcq->setMsgTemplate(json_obj["msgTemplate"].toString());
        result = MsgIcq;
        } break;
    case TActionID::MsgJabber: {
        SendMessageToJabberAction *MsgJabber = new SendMessageToJabberAction();
        MsgJabber->setSendMessage(json_obj["sendMessage"].toString());
        MsgJabber->setMsgTemplate(json_obj["msgTemplate"].toString());
        result = MsgJabber;
        } break;
    case TActionID::LogRecord: {
        RecordSdpoLogAction *LogRecord = new RecordSdpoLogAction();
        LogRecord->setAddCommonLog(json_obj["addCommonLog"].toBool());
        LogRecord->setAddPrivateLog(json_obj["addPrivateLog"].toBool());
        LogRecord->setAddSpecificLog(json_obj["addSpecificLog"].toBool());
        LogRecord->setSpecificLogFile(json_obj["specificLogFile"].toString());
        result = LogRecord;
        } break;
    case TActionID::Report: {
        GenerateReportsAction *Report = new GenerateReportsAction();
        Report->setGenerateReportFolder(json_obj["generateReportFolder"].toBool());
        Report->setGenerateReportSpecificFolder(json_obj["generateReportFolderSpecific"].toBool());
        Report->setReportSelect(json_obj["reportSelect"].toString());
        Report->setRecursiveMode(json_obj["recursiveMode"].toString());
        Report->setUseReportPool(json_obj["useReportPool"].toBool());
        result = Report;
        } break;
    case TActionID::ServiceStop: {
        StopServiceAction *ServiceStop = new StopServiceAction();
        ServiceStop->setStopServiceOn(json_obj["stopServiceOn"].toString());
        ServiceStop->setServiceName(json_obj["serviceName"].toString());
        ServiceStop->setParameters(json_obj["parameters"].toString());
        ServiceStop->setConnectAs(json_obj["connectAs"].toBool());
        ServiceStop->setConnectAsLogin(json_obj["connectAsLogin"].toString());
        ServiceStop->setConnectAsPassword(json_obj["connectAsPassword"].toString());
        result = ServiceStop;
        } break;
    case TActionID::ServiceStart: {
        StartServiceAction *ServiceStart = new StartServiceAction();
        ServiceStart->setStartServiceOn(json_obj["startServiceOn"].toString());
        ServiceStart->setServiceName(json_obj["serviceName"].toString());
        ServiceStart->setParameters(json_obj["parameters"].toString());
        ServiceStart->setConnectAs(json_obj["connectAs"].toBool());
        ServiceStart->setConnectAsLogin(json_obj["connectAsLogin"].toString());
        ServiceStart->setConnectAsPassword(json_obj["connectAsPassword"].toString());
        result = ServiceStart;
        } break;
    case TActionID::ServiceRestart: {
        RestartServiceAction *ServiceRestart = new RestartServiceAction();
        ServiceRestart->setRestartServiceOn(json_obj["restartServiceOn"].toString());
        ServiceRestart->setServiceName(json_obj["serviceName"].toString());
        ServiceRestart->setDoNotStartService(json_obj["doNotStartService"].toBool());
        ServiceRestart->setConnectAs(json_obj["connectAs"].toBool());
        ServiceRestart->setConnectAsLogin(json_obj["connectAsLogin"].toString());
        ServiceRestart->setConnectAsPassword(json_obj["connectAsPassword"].toString());
        result = ServiceRestart;
        } break;
    case TActionID::RebootRemote: {
        RebootRemoteSystemAction *RebootRemote = new RebootRemoteSystemAction();
        RebootRemote->setComputerName(json_obj["computerName"].toString());
        RebootRemote->setMessageToDisplay(json_obj["messageToDisplay"].toString());
        RebootRemote->setTimeToDisplay(json_obj["timeToDisplay"].toInt());
        RebootRemote->setMethod(json_obj["method"].toString());
        RebootRemote->setForceProcesses(json_obj["forceProcesses"].toBool());
        result = RebootRemote;
        } break;
    case TActionID::RebootLocal: {
        RebootLocalMachineAction *RebootLocal = new RebootLocalMachineAction();
        RebootLocal->setLogout(json_obj["logout"].toBool());
        RebootLocal->setReboot(json_obj["reboot"].toBool());
        RebootLocal->setShutdown(json_obj["shutdown"].toBool());
        RebootLocal->setPowerOff(json_obj["powerOff"].toBool());
        RebootLocal->setForceProcesses(json_obj["forceProcesses"].toBool());
        result = RebootLocal;
        } break;
    case TActionID::DialUpConnect: {
        DialupToTheNetworkAction *DialUpConnect = new DialupToTheNetworkAction();
        DialUpConnect->setDialUpConnection(json_obj["dialUpConnection"].toString());
        DialUpConnect->setUserName(json_obj["userName"].toString());
        DialUpConnect->setPassword(json_obj["password"].toString());
        DialUpConnect->setSavePassword(json_obj["savePassword"].toBool());
        DialUpConnect->setShowDialUpWindow(json_obj["showDialUpWindow"].toBool());
        DialUpConnect->setRetries(json_obj["retries"].toInt());
        result = DialUpConnect;
        } break;
    case TActionID::DialUpDisconnect: {
        DisconnectDialupConnectionAction *DialUpDisconnect = new DisconnectDialupConnectionAction();
        DialUpDisconnect->setDialUpConnection(json_obj["dialUpDisconnect"].toString());
        result = DialUpDisconnect;
        } break;
    case TActionID::ProgramExec: {
        ExecuteExternalProgramAction *ProgramExec = new ExecuteExternalProgramAction();
        ProgramExec->setCommandLine(json_obj["commandLine"].toString());
        ProgramExec->setWindowMode(json_obj["windowMode"].toString());
        result = ProgramExec;
        } break;
    case TActionID::LogEvent: {
        LogEventAction *LogEvent = new LogEventAction();
        LogEvent->setComputer(json_obj["computer"].toString());
        LogEvent->setLog(json_obj["log"].toString());
        LogEvent->setEventType(json_obj["eventType"].toString());
        LogEvent->setEventSource(json_obj["eventSource"].toString());
        LogEvent->setEventId(json_obj["eventId"].toInt());
        LogEvent->setDescription(json_obj["description"].toString());
        LogEvent->setConnectAs(json_obj["connectAs"].toBool());
        LogEvent->setLogin(json_obj["login"].toString());
        LogEvent->setPassword(json_obj["password"].toString());
        result = LogEvent;
        } break;
    case TActionID::SqlQuery: {
        SqlQueryAction *SqlQuery = new SqlQueryAction();
        SqlQuery->setOdbcDataSource(json_obj["odbcDataSource"].toString());
        SqlQuery->setLogin(json_obj["login"].toString());
        SqlQuery->setPassword(json_obj["password"].toString());
        SqlQuery->setSqlQuery(json_obj["sqlQuery"].toString());
        SqlQuery->setTimeout(json_obj["timeout"].toInt());
        result = SqlQuery;
        } break;
    case TActionID::HttpRequest: {
        HttpRequestAction *HttpRequest = new HttpRequestAction();
        HttpRequest->setHost(json_obj["host"].toString());
        HttpRequest->setPort(json_obj["port"].toInt());
        HttpRequest->setRequest(json_obj["request"].toString());
        result = HttpRequest;
        } break;
    case TActionID::SendData: {
        SendDataToTcpUdpPortAction *SendData = new SendDataToTcpUdpPortAction();
        SendData->setServer(json_obj["server"].toString());
        SendData->setProtocol(json_obj["protocol"].toString());
        SendData->setPort(json_obj["port"].toInt());
        SendData->setInitPacket(json_obj["initPacket"].toString());
        SendData->setWaitForAnswer(json_obj["waitForAnswer"].toInt());
        SendData->setFinalPacket(json_obj["finalPacket"].toString());
        result = SendData;
        } break;
    case TActionID::Syslog: {
        SyslogAction *Syslog = new SyslogAction();
        Syslog->setServer(json_obj["server"].toString());
        Syslog->setPort(json_obj["port"].toInt());
        Syslog->setMessage(json_obj["message"].toString());
        Syslog->setSeverity(json_obj["severity"].toString());
        Syslog->setFacility(json_obj["facility"].toInt());
        result = Syslog;
        } break;
    case TActionID::SnmpSet: {
        SnmpSetAction *SnmpSet = new SnmpSetAction();
        SnmpSet->setAgentAddress(json_obj["agentAddress"].toString());
        SnmpSet->setTimeout(json_obj["timeout"].toInt());
        SnmpSet->setSnmpProfile(json_obj["community"].toString());
        SnmpSet->setRetries(json_obj["retries"].toInt());
        SnmpSet->setOid(json_obj["oid"].toString());
        SnmpSet->setSetValue(json_obj["setValue"].toString());
        result = SnmpSet;
        } break;
    case TActionID::SnmpTrap: {
        SnmpTrapAction *SnmpTrap = new SnmpTrapAction();
        SnmpTrap->setDestAddress(json_obj["destAddress"].toString());
        SnmpTrap->setCommunity(json_obj["community"].toString());
        SnmpTrap->setAgentAddress(json_obj["agentAddress"].toString());
        SnmpTrap->setEnterprise(json_obj["enterprise"].toString());
        SnmpTrap->setTrapType(json_obj["trapType"].toString());
        SnmpTrap->setSpecific(json_obj["specific"].toInt());
        SnmpTrap->setMibOid(json_obj["mibOid"].toString());
        SnmpTrap->setMibValue(json_obj["mibValue"].toString());
        SnmpTrap->setMibType(json_obj["mibType"].toString());
        result = SnmpTrap;
        } break;
    case TActionID::TestRepeat: {
        RepeatTestAction *TestRepeat = new RepeatTestAction();
        TestRepeat->setRepeatTest(json_obj["repeatTest"].toBool());
        TestRepeat->setRecheckTest(json_obj["recheckTest"].toBool());
        result = TestRepeat;
        } break;
    case TActionID::TestInterval: {
        ChangeTestIntervalAction *TestInterval = new ChangeTestIntervalAction();
        TestInterval->setRestoreValue(json_obj["restoreValue"].toBool());
        TestInterval->setSetToTime(json_obj["setToTime"].toBool());
        TestInterval->setTimeValueSelect(QTime::fromString(json_obj["timeValueSelect"].toString(),"hh:mm:ss"));
        TestInterval->setSetToPercent(json_obj["setToPercent"].toBool());
        TestInterval->setPercent(json_obj["percent"].toInt());
        result = TestInterval;
        } break;
    case TActionID::RunScript: {
        RunHmsScriptAction *RunScript = new RunHmsScriptAction();
        RunScript->setScriptFile(json_obj["scriptFile"].toString());
        result = RunScript;
        } break;
    default:
        result = new TestAction();
        result->setAction(id);
    }
    result->setName(json_obj["name"].toString());
    result->setAgent(json_obj["agent"].toString());
    result->setStoreResult(json_obj["storeResult"].toBool());
    result->setMode(static_cast<TActionMode>(json_obj["mode"].toInt()));
    result->setStartAfter(json_obj["startAfter"].toInt());
    result->setRetries(json_obj["retries"].toInt());
    result->setCondition(json_obj["condition"].toString());
    return result;
}

/*****************************************************************/

QJsonDocument IOActionProfileLoader::createJsonDocument()
{
    QJsonArray jsonArray;
    foreach (const GActionProfile &profile, GData::actionProfiles) {
         QJsonObject jsonObj;
         jsonObj.insert("name",QJsonValue(profile.name));

         QJsonArray onBad_array;
         foreach(TestAction *action, profile.onBad) {
             onBad_array.append(createActionValue(action));
         }
         jsonObj.insert("onBad", QJsonValue(onBad_array));

         QJsonArray onGood_array;
         foreach(TestAction *action, profile.onGood) {
             onGood_array.append(createActionValue(action));
         }
         jsonObj.insert("onGood", QJsonValue(onGood_array));

         QJsonArray comments_array;
         foreach(const QString &line, profile.comments) {
             comments_array.append(QJsonValue(line));
         }
         jsonObj.insert("comment", QJsonValue(comments_array));
         jsonArray.append(QJsonValue(jsonObj));
    }
    QJsonDocument jsonDoc(jsonArray);
    return jsonDoc;
}

/*****************************************************************/

QJsonValue IOActionProfileLoader::createActionValue(TestAction *action)
{
    QJsonObject jsonObj;
    TActionID id = action->getAction();
    jsonObj.insert("action", QJsonValue(TAction::toCode(id)));
    jsonObj.insert("name", QJsonValue(action->getName()));
    jsonObj.insert("agent", QJsonValue(action->getAgent()));
    jsonObj.insert("storeResult", QJsonValue(action->isStoreResult()));
    jsonObj.insert("mode", QJsonValue(static_cast<int>(action->getMode())));
    jsonObj.insert("startAfter", QJsonValue(action->getStartAfter()));
    jsonObj.insert("retries", QJsonValue(action->getRetries()));
    jsonObj.insert("condition", QJsonValue(action->getCondition()));
    switch (id) {
    case TActionID::WinPopup:
        break;
    case TActionID::PlaySound: {
        PlaySoundAction *playSound = qobject_cast<PlaySoundAction*>(action);
        jsonObj.insert("file", QJsonValue(playSound->getFile()));
        jsonObj.insert("wakeUp", QJsonValue(playSound->isWakeUp()));
    } break;
    case TActionID::MsgPagerTap: {
        SendMessageToPagerTapAction *msgPagerTap = qobject_cast<SendMessageToPagerTapAction*>(action);
        jsonObj.insert("accessNumber", QJsonValue(msgPagerTap->getAccessNumber()));
        jsonObj.insert("password", QJsonValue(msgPagerTap->getPassword()));
        jsonObj.insert("maxCharacter", QJsonValue(msgPagerTap->getMaxCharacter()));
        jsonObj.insert("parity", QJsonValue(msgPagerTap->getParity()));
        jsonObj.insert("pagerId", QJsonValue(msgPagerTap->getPagerId()));
        jsonObj.insert("msgTemplate", QJsonValue(msgPagerTap->getMsgTemplate()));
    } break;
    case TActionID::MsgPagerSnpp: {
        SendMessageToPagerSnppAction *msgPagerSnpp = qobject_cast<SendMessageToPagerSnppAction*>(action);
        jsonObj.insert("pajerID", QJsonValue(msgPagerSnpp->getPagerID()));
        jsonObj.insert("mailTemplate", QJsonValue(msgPagerSnpp->getMailTemplate()));
        jsonObj.insert("level", QJsonValue(msgPagerSnpp->getLevel()));
        jsonObj.insert("alert", QJsonValue(msgPagerSnpp->isAlert()));
        jsonObj.insert("server", QJsonValue(msgPagerSnpp->getServer()));
        jsonObj.insert("port", QJsonValue(msgPagerSnpp->getPort()));
        jsonObj.insert("loginAs", QJsonValue(msgPagerSnpp->isLoginAs()));
        jsonObj.insert("loginAsLogin", QJsonValue(msgPagerSnpp->getLoginAsLogin()));
        jsonObj.insert("loginAsPassword", QJsonValue(msgPagerSnpp->getLoginAsPassword()));
    } break;
    case TActionID::MsgBeeper: {
        SendMessageToBeeperAction *MsgBeeper = qobject_cast<SendMessageToBeeperAction*>(action);
        jsonObj.insert("beeper", QJsonValue(MsgBeeper->getBeeper()));
        jsonObj.insert("delay", QJsonValue(MsgBeeper->getDelay()));
        jsonObj.insert("sendMessage", QJsonValue(MsgBeeper->getSendMessage()));
        jsonObj.insert("terminationString", QJsonValue(MsgBeeper->getTerminationString()));
    } break;
    case TActionID::MsgSmsGsm: {
        SendSmsGsmModemAction *MsgSmsGsm = qobject_cast<SendSmsGsmModemAction*>(action);
        jsonObj.insert("destPhone", QJsonValue(MsgSmsGsm->getDestPhone()));
        jsonObj.insert("msgClass", QJsonValue(MsgSmsGsm->getMsgClass()));
        jsonObj.insert("msgTemplate", QJsonValue(MsgSmsGsm->getMsgTemplate()));
    } break;
    case TActionID::MsgSmsSmpp: {
        SendSmsSmppAction *MsgSmsSmpp = qobject_cast<SendSmsSmppAction*>(action);
        jsonObj.insert("destPhone", QJsonValue(MsgSmsSmpp->getDestPhone()));
        jsonObj.insert("msgClass", QJsonValue(MsgSmsSmpp->getDestTon()));
        jsonObj.insert("msgTemplate", QJsonValue(MsgSmsSmpp->getDestNpi()));
        jsonObj.insert("msgTemplate", QJsonValue(MsgSmsSmpp->getMsgTemplate()));
    } break;
    case TActionID::MsgEmail: {
        SendEmailSmtpAction *MsgEmail = qobject_cast<SendEmailSmtpAction*>(action);
        jsonObj.insert("fromSender", QJsonValue(MsgEmail->getFromSender()));
        jsonObj.insert("toRecipient", QJsonValue(MsgEmail->getToRecipients()));
        jsonObj.insert("priority", QJsonValue(MsgEmail->getPriority()));
        jsonObj.insert("subject", QJsonValue(MsgEmail->getSubject()));
        jsonObj.insert("bodyTemplate", QJsonValue(MsgEmail->getBodyTemplate()));
        jsonObj.insert("attachFile", QJsonValue(MsgEmail->isAttachFile()));
        jsonObj.insert("attachFileSelect", QJsonValue(MsgEmail->getAttachFileSelect()));
    } break;
    case TActionID::MsgIcq: {
        SendMessageToIcqAction *MsgIcq = qobject_cast<SendMessageToIcqAction*>(action);
        jsonObj.insert("sendMessage", QJsonValue(MsgIcq->getSendMessage()));
        jsonObj.insert("msgTemplate", QJsonValue(MsgIcq->getMsgTemplate()));
    } break;
    case TActionID::MsgJabber: {
        SendMessageToJabberAction *MsgJabber = qobject_cast<SendMessageToJabberAction*>(action);
        jsonObj.insert("sendMessage", QJsonValue(MsgJabber->getSendMessage()));
        jsonObj.insert("msgTemplate", QJsonValue(MsgJabber->getMsgTemplate()));
    } break;
    case TActionID::LogRecord: {
        RecordSdpoLogAction *LogRecord = qobject_cast<RecordSdpoLogAction*>(action);
        jsonObj.insert("addCommonLog", QJsonValue(LogRecord->isAddCommonLog()));
        jsonObj.insert("addPrivateLog", QJsonValue(LogRecord->isAddPrivateLog()));
        jsonObj.insert("addSpecificLog", QJsonValue(LogRecord->isAddSpecificLog()));
        jsonObj.insert("specificLogFile", QJsonValue(LogRecord->getSpecificLogFile()));
    } break;
    case TActionID::Report: {
        GenerateReportsAction *Report = qobject_cast<GenerateReportsAction*>(action);
        jsonObj.insert("generateReportFolder", QJsonValue(Report->isGenerateReportFolder()));
        jsonObj.insert("generateReportFolderSpecific", QJsonValue(Report->isGenerateReportSpecificFolder()));
        jsonObj.insert("reportSelect", QJsonValue(Report->getReportSelect()));
        jsonObj.insert("recursiveMode", QJsonValue(Report->getRecursiveMode()));
        jsonObj.insert("useReportPool", QJsonValue(Report->isUseReportPool()));
    } break;
    case TActionID::ServiceStop: {
        StopServiceAction *ServiceStop = qobject_cast<StopServiceAction*>(action);
        jsonObj.insert("stopServiceOn", QJsonValue(ServiceStop->getStopServiceOn()));
        jsonObj.insert("serviceName", QJsonValue(ServiceStop->getServiceName()));
        jsonObj.insert("parameters", QJsonValue(ServiceStop->getParameters()));
        jsonObj.insert("connectAs", QJsonValue(ServiceStop->isConnectAs()));
        jsonObj.insert("connectAsLogin", QJsonValue(ServiceStop->getConnectAsLogin()));
        jsonObj.insert("connectAsPassword", QJsonValue(ServiceStop->getConnectAsPassword()));
    } break;
    case TActionID::ServiceStart: {
        StartServiceAction *ServiceStart = qobject_cast<StartServiceAction*>(action);
        jsonObj.insert("startServiceOn", QJsonValue(ServiceStart->getStartServiceOn()));
        jsonObj.insert("serviceName", QJsonValue(ServiceStart->getServiceName()));
        jsonObj.insert("parameters", QJsonValue(ServiceStart->getParameters()));
        jsonObj.insert("connectAs", QJsonValue(ServiceStart->isConnectAs()));
        jsonObj.insert("connectAsLogin", QJsonValue(ServiceStart->getConnectAsLogin()));
        jsonObj.insert("connectAsPassword", QJsonValue(ServiceStart->getConnectAsPassword()));
    } break;
    case TActionID::ServiceRestart: {
        RestartServiceAction *ServiceRestart = qobject_cast<RestartServiceAction*>(action);
        jsonObj.insert("restartServiceOn", QJsonValue(ServiceRestart->getRestartServiceOn()));
        jsonObj.insert("serviceName", QJsonValue(ServiceRestart->getServiceName()));
        jsonObj.insert("doNotStartService", QJsonValue(ServiceRestart->isDoNotStartService()));
        jsonObj.insert("connectAs", QJsonValue(ServiceRestart->isConnectAs()));
        jsonObj.insert("connectAsLogin", QJsonValue(ServiceRestart->getConnectAsLogin()));
        jsonObj.insert("connectAsPassword", QJsonValue(ServiceRestart->getConnectAsPassword()));
    } break;
    case TActionID::RebootRemote: {
        RebootRemoteSystemAction *RebootRemote = qobject_cast<RebootRemoteSystemAction*>(action);
        jsonObj.insert("computerName", QJsonValue(RebootRemote->getComputerName()));
        jsonObj.insert("messageToDisplay", QJsonValue(RebootRemote->getMessageToDisplay()));
        jsonObj.insert("timeToDisplay", QJsonValue(RebootRemote->getTimeToDisplay()));
        jsonObj.insert("method", QJsonValue(RebootRemote->getMethod()));
        jsonObj.insert("forceProcesses", QJsonValue(RebootRemote->isForceProcesses()));
    } break;
    case TActionID::RebootLocal: {
        RebootLocalMachineAction *RebootLocal = qobject_cast<RebootLocalMachineAction*>(action);
        jsonObj.insert("logout", QJsonValue(RebootLocal->isLogout()));
        jsonObj.insert("reboot", QJsonValue(RebootLocal->isReboot()));
        jsonObj.insert("shutdown", QJsonValue(RebootLocal->isShutdown()));
        jsonObj.insert("powerOff", QJsonValue(RebootLocal->isPowerOff()));
        jsonObj.insert("forceProcesses", QJsonValue(RebootLocal->isForceProcesses()));
    } break;
    case TActionID::DialUpConnect: {
        DialupToTheNetworkAction *DialUpConnect = qobject_cast<DialupToTheNetworkAction*>(action);
        jsonObj.insert("dialUpConnection", QJsonValue(DialUpConnect->getDialUpConnection()));
        jsonObj.insert("userName", QJsonValue(DialUpConnect->getUserName()));
        jsonObj.insert("password", QJsonValue(DialUpConnect->getPassword()));
        jsonObj.insert("savePassword", QJsonValue(DialUpConnect->isSavePassword()));
        jsonObj.insert("showDialUpWindow", QJsonValue(DialUpConnect->isShowDialUpWindow()));
        jsonObj.insert("retries", QJsonValue(DialUpConnect->getRetries()));
    } break;
    case TActionID::DialUpDisconnect: {
        DisconnectDialupConnectionAction *DialUpDisconnect = qobject_cast<DisconnectDialupConnectionAction*>(action);
        jsonObj.insert("dialUpDisconnect", QJsonValue(DialUpDisconnect->getDialUpConnection()));
    } break;
    case TActionID::ProgramExec: {
        ExecuteExternalProgramAction *ProgramExec = qobject_cast<ExecuteExternalProgramAction*>(action);
        jsonObj.insert("commandLine", QJsonValue(ProgramExec->getCommandLine()));
        jsonObj.insert("windowMode", QJsonValue(ProgramExec->getWindowMode()));
    } break;
    case TActionID::LogEvent: {
        LogEventAction *LogEvent = qobject_cast<LogEventAction*>(action);
        jsonObj.insert("computer", QJsonValue(LogEvent->getComputer()));
        jsonObj.insert("log", QJsonValue(LogEvent->getLog()));
        jsonObj.insert("eventType", QJsonValue(LogEvent->getEventType()));
        jsonObj.insert("eventSource", QJsonValue(LogEvent->getEventSource()));
        jsonObj.insert("eventId", QJsonValue(LogEvent->getEventId()));
        jsonObj.insert("description", QJsonValue(LogEvent->getDescription()));
        jsonObj.insert("connectAs", QJsonValue(LogEvent->isConnectAs()));
        jsonObj.insert("login", QJsonValue(LogEvent->getLogin()));
        jsonObj.insert("password", QJsonValue(LogEvent->getPassword()));
    } break;
    case TActionID::SqlQuery: {
        SqlQueryAction *SqlQuery = qobject_cast<SqlQueryAction*>(action);
        jsonObj.insert("odbcDataSource", QJsonValue(SqlQuery->getOdbcDataSource()));
        jsonObj.insert("login", QJsonValue(SqlQuery->getLogin()));
        jsonObj.insert("password", QJsonValue(SqlQuery->getPassword()));
        jsonObj.insert("sqlQuery", QJsonValue(SqlQuery->getSqlQuery()));
        jsonObj.insert("timeout", QJsonValue(SqlQuery->getTimeout()));
    } break;
    case TActionID::HttpRequest: {
        HttpRequestAction *HttpRequest = qobject_cast<HttpRequestAction*>(action);
        jsonObj.insert("host", QJsonValue(HttpRequest->getHost()));
        jsonObj.insert("port", QJsonValue(HttpRequest->getPort()));
        jsonObj.insert("request", QJsonValue(HttpRequest->getRequest()));
    } break;
    case TActionID::SendData: {
        SendDataToTcpUdpPortAction *SendData = qobject_cast<SendDataToTcpUdpPortAction*>(action);
        jsonObj.insert("server", QJsonValue(SendData->getServer()));
        jsonObj.insert("protocol", QJsonValue(SendData->getProtocol()));
        jsonObj.insert("port", QJsonValue(SendData->getPort()));
        jsonObj.insert("initPacket", QJsonValue(SendData->getInitPacket()));
        jsonObj.insert("waitForAnswer", QJsonValue(SendData->getWaitForAnswer()));
        jsonObj.insert("finalPacket", QJsonValue(SendData->getFinalPacket()));
    } break;
    case TActionID::Syslog: {
        SyslogAction *Syslog = qobject_cast<SyslogAction*>(action);
        jsonObj.insert("server", QJsonValue(Syslog->getServer()));
        jsonObj.insert("port", QJsonValue(Syslog->getPort()));
        jsonObj.insert("message", QJsonValue(Syslog->getMessage()));
        jsonObj.insert("severity", QJsonValue(Syslog->getSeverity()));
        jsonObj.insert("facility", QJsonValue(Syslog->getFacility()));
    } break;
    case TActionID::SnmpSet: {
        SnmpSetAction *SnmpSet = qobject_cast<SnmpSetAction*>(action);
        jsonObj.insert("agentAddress", QJsonValue(SnmpSet->getAgentAddress()));
        jsonObj.insert("timeout", QJsonValue(SnmpSet->getTimeout()));
        jsonObj.insert("community", QJsonValue(SnmpSet->getSnmpProfile()));
        jsonObj.insert("retries", QJsonValue(SnmpSet->getRetries()));
        jsonObj.insert("oid", QJsonValue(SnmpSet->getOid()));
        jsonObj.insert("setValue", QJsonValue(SnmpSet->getSetValue()));
    } break;
    case TActionID::SnmpTrap: {
        SnmpTrapAction *SnmpTrap = qobject_cast<SnmpTrapAction*>(action);
        jsonObj.insert("destAddress", QJsonValue(SnmpTrap->getDestAddress()));
        jsonObj.insert("community", QJsonValue(SnmpTrap->getCommunity()));
        jsonObj.insert("agentAddress", QJsonValue(SnmpTrap->getAgentAddress()));
        jsonObj.insert("enterprise", QJsonValue(SnmpTrap->getEnterprise()));
        jsonObj.insert("trapType", QJsonValue(SnmpTrap->getTrapType()));
        jsonObj.insert("specific", QJsonValue(SnmpTrap->getSpecific()));
        jsonObj.insert("mibOid", QJsonValue(SnmpTrap->getMibOid()));
        jsonObj.insert("mibValue", QJsonValue(SnmpTrap->getMibValue()));
        jsonObj.insert("mibType", QJsonValue(SnmpTrap->getMibType()));
    } break;
    case TActionID::TestRepeat: {
        RepeatTestAction *TestRepeat = qobject_cast<RepeatTestAction*>(action);
        jsonObj.insert("repeatTest", QJsonValue(TestRepeat->isRepeatTest()));
        jsonObj.insert("recheckTest", QJsonValue(TestRepeat->isRecheckTest()));
    } break;
    case TActionID::TestInterval: {
        ChangeTestIntervalAction *TestInterval = qobject_cast<ChangeTestIntervalAction*>(action);
        jsonObj.insert("restoreValue", QJsonValue(TestInterval->isRestoreValue()));
        jsonObj.insert("setToTime", QJsonValue(TestInterval->isSetToTime()));
        jsonObj.insert("timeValueSelect", QJsonValue(TestInterval->getTimeValueSelect().toString("hh:mm:ss")));
        jsonObj.insert("setToPercent", QJsonValue(TestInterval->isSetToPercent()));
        jsonObj.insert("percent", QJsonValue(TestInterval->getPercent()));
    } break;
    case TActionID::RunScript: {
        RunHmsScriptAction *RunScript = qobject_cast<RunHmsScriptAction*>(action);
        jsonObj.insert("scriptFile", QJsonValue(RunScript->getScriptFile()));
    } break;
    default:
        break;
    }
    return QJsonValue(jsonObj);
}

/*****************************************************************/

} // namespace SDPO
