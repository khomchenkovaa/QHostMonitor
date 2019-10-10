#include "tAction.h"

namespace SDPO {

/*****************************************************************/

QVector<TAction> TAction::actionList;

/*****************************************************************/

void TAction::init()
{
    append(TActionID::WinPopup,"WinPopup","Show popup window");
    append(TActionID::PlaySound,"PlaySound","Play sound");
    append(TActionID::MsgPagerTap,"MsgPagerTap","Send message to pager (TAP)");
    append(TActionID::MsgPagerSnpp,"MsgPagerSnpp","Send message to pager (SNPP)");
    append(TActionID::MsgBeeper,"MsgBeeper","Send message to beeper");
    append(TActionID::MsgSmsGsm,"MsgSmsGsm","Send SMS (GSM modem)");
    append(TActionID::MsgSmsSmpp,"MsgSmsSmpp","Send SMS (SMPP over IP)");
    append(TActionID::MsgEmail,"MsgEmail","Send e-mail (SMTP)");
    append(TActionID::MsgIcq,"MsgIcq","Send message to ICQ");
    append(TActionID::MsgJabber,"MsgJabber","Send message to Jabber");
    append(TActionID::LogRecord,"LogRecord","Record HM log");
    append(TActionID::Report,"Report","Generate reports");
    append(TActionID::ServiceStop,"ServiceStop","Stop service");
    append(TActionID::ServiceStart,"ServiceStart","Start service");
    append(TActionID::ServiceRestart,"ServiceRestart","Restart service");
    append(TActionID::RebootRemote,"RebootRemote","Reboot remote system");
    append(TActionID::RebootLocal,"RebootLocal","Reboot local machine");
    append(TActionID::DialUpConnect,"DialUpConnect","Dial-up to the network");
    append(TActionID::DialUpDisconnect,"DialUpDisconnect","Disconnect dial-up connection");
    append(TActionID::ProgramExec,"ProgramExec","Execute external program");
    append(TActionID::LogEvent,"LogEvent","Log Event");
    append(TActionID::SqlQuery,"SqlQuery","SQL Query");
    append(TActionID::HttpRequest,"HttpRequest","HTTP request");
    append(TActionID::SendData,"SendData","Send data to TCP/UDP port");
    append(TActionID::Syslog,"Syslog","Syslog");
    append(TActionID::SnmpSet,"SnmpSet","SNMP Set");
    append(TActionID::SnmpTrap,"SnmpTrap","SNMP Trap");
    append(TActionID::TestRepeat,"TestRepeat","Repeat test");
    append(TActionID::TestInterval,"TestInterval","Change test interval");
    append(TActionID::RunScript,"RunScript","Run HMS script");
    append(TActionID::NoAction,"NoAction","");
}

/*****************************************************************/

void TAction::append(TActionID actionId, QString actionCode, QString actionName)
{
    TAction action;
    action.id = actionId;
    action.code = actionCode;
    action.name = actionName;
    actionList.append(action);
}

/*****************************************************************/

QString TAction::toCode(TActionID id)
{
    return TAction::actionList.at(static_cast<int>(id)).code;
}

/*****************************************************************/

TActionID TAction::fromCode(const QString value)
{
    TActionID result = TActionID::NoAction;
    foreach(const TAction &action, actionList) {
        if (action.code == value) {
            result = action.id;
            break;
        }
    }
    return result;
}

/*****************************************************************/

} // namespace SDPO
