#ifndef TACTION_H
#define TACTION_H

#include <QString>
#include <QVector>

namespace SDPO {

/*****************************************************************/

enum class TActionID {
    WinPopup, // Show popup window
    PlaySound, // Play sound
    MsgPagerTap, // Send message to pager (TAP)
    MsgPagerSnpp, // Send message to pager (SNPP)
    MsgBeeper, // Send message to beeper
    MsgSmsGsm, // Send SMS (GSM modem)
    MsgSmsSmpp, // Send SMS (SMPP over IP)
    MsgEmail, // Send e-mail (SMTP)
    MsgIcq, // Send message to ICQ
    MsgJabber, // Send message to Jabber
    LogRecord, // Record HM log
    Report, // Generate reports
    ServiceStop, // Stop service
    ServiceStart, // Start service
    ServiceRestart, // Restart service
    RebootRemote, // Reboot remote system
    RebootLocal, // Reboot local machine
    DialUpConnect, // Dial-up to the network
    DialUpDisconnect, // Disconnect dial-up connection
    ProgramExec, // Execute external program
    LogEvent, // Log Event
    SqlQuery, // SQL Query
    HttpRequest, // HTTP request
    SendData, // Send data to TCP/UDP port
    Syslog, // Syslog
    SnmpSet, // SNMP Set
    SnmpTrap, // SNMP Trap
    TestRepeat, // Repeat test
    TestInterval, // Change test interval
    RunScript, // Run HMS script
    NoAction
};

/*****************************************************************/

enum class TActionMode {
    Standard, // standard mode
    Advanced, // advanced mode
    Schedule  // on the schedule
};

/*****************************************************************/

class TAction
{
public:
    TActionID id;
    QString code;
    QString name;

    static QVector<TAction> actionList;

    static void init();
    static void append(TActionID actionId, QString actionCode, QString actionName);
    static QString toCode(TActionID id);
    static TActionID fromCode(const QString value);
};

/*****************************************************************/

} // namespace SDPO

#endif // TACTION_H
