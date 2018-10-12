#ifndef SETTINGS_H
#define SETTINGS_H

#include "gSettings.h"

#include <QVariant>
#include <QSettings>
#include <QMetaEnum>

namespace SDPO {

/**
  @brief Синглтон для доступа к конфигурации

  Usage:
  @code
    ...
    ...
    //пердварительная настройка (должен быть где-нибуль в main)
    QApplication::setOrganizationName("Organization name");
    QApplication::setApplicationName("App name");
    ...
    ...
    void fun(){
        ...
        QVariant val1 = Settings::get(Settings::SomeSection, Settings::SomeKey);
        Settings::set(Settings::SomeSection, Settings::SomeKey) = "new val1";
        ...
    }
  @endcode
*/
class Settings : public QObject {
    Q_OBJECT
    Q_ENUMS(Section)
    Q_ENUMS(Key)
public:
    enum Section{
        HostMonitor,
        IP_Monitor,
        Environ,
        Telnet,
        LogViewer,
        Ping_Trace,
        Language,
        HostMon,
        SMTP,
        LogViewers,
        TxtLogViewer,
        LogAnalizer,
        Pagers,
        Reports,
        Service,
        Misc,
        FixedFormats,
        Interface,
        MonitorColumns,
        SortingColumns,
        RecentList1,
        Logging,
        Logging1,
        Logging2,
        Logging_CommonProcessing,
        Logging_PrivProcessing,
        ICQ,
        UpdateCheck,
        GSM,
        Jabber,
        SMS_SMPP1,
        SMS_SMPP2,
        RCI,
        Scheduler,
        TrapListener,
        ActiveRMAServer
    };

    enum Key{
        // Environ
            //PingOption
        ClearOldInfo, // 0
        ShowHostsDescription, // 1
            //Preference
        FontName, // MS Sans Serif
        FontSize, //8
        TelnetFontName, //Terminal
        TelnetFontSize, //12
        AutoSave, //1
        MinToTray, //1
        StayFormTop, //0
        KeptAddresses, //1
        DeepAddresses, //5
        AnimateIcon, //1
        ChangeIcon, //1
        AutoSaveMode, //1
            //StartupOption
        StartStopMode, //2
        WinStatusMode, //3
        FileLoadMode, //2
        ErrorHandlerMode, //1
        LoadFileName, //  
            //Misc(Reports)
        DigitsAfterDotStat,//2
        // Ping_Trace
        TTL, // 255
        Timeout, // 1000 + //RCI = 300
        PacketSize, // 32
        Packets, // 1
        Hops, // 32
        StopTrace, // 1
        // HostMon
        MsgWinTime, // 5
        MsgWinXPos, // 200
        MsgWinYPos, // 100
        MsgWinConstPos, // 0
        MsgWinCloseAuto, // 1
        MsgWinStayTop, // 1
            //Access method
        AccessMethod, //0
            //Proxy
        ProxyServer, //127.0.0.1
        ProxyPort, //80
        ProxyAut, //0
        ProxyUser, //
        ProxyPswd, //
        ProxyParam2, //FF50
            //StartupOption
        StartupRun, //0
            //Behavior
        RefreshMode, // 2
        MaxThreads, // 32
        MastersLifetime, // 60
        RecheckDependants, // 0
        CommentForDisabling, // 0
            //Misc(Settings for Url)
        CheckInternetConnection, //1
        //SMTP
            //Mailer Settings
        SMTPServer, //smtp.mail.yahoo.com
        SMTPPort, //25
        ShowMailWin, //1
        ShowMailWinInLastPos, //1
        MailWinAutoClose, //1
        MailWinCloseAfter, //6
        SMTPServer2, //smtp.mail.yahoo.com
        SMTPPort2, //25
        Authentication1, //0
        Username1, //
        Password1, //
        Authentication2, //0
        Username2, //
        Password2, //
        SSLType1, //0
        SSLType2, //0
        //LogViewer
            //Viewers
        TextViewerMode, //0
        HTMLViewerMode, //1
        DBFViewerMode, //0
        TextViewerCmd, //notepad.exe %log%
        HTMLViewerCmd, //
        DBFViewerCmd, //
        //Pagers
            //Pagers
        pgDevice, //Auto select free TAPI device
        pgBoudRate, //2400
        pgInitStr, //AUTO
        pgDialStr, //ATDT
        pgShowWindow, //1
        pgCloseWindow, //1
        pgCloseDelay, //5
        pgWaitFreeDevice, //1
        pgWaitDeviceDelay, //15
        //Reports
            //Reports
        AutoCreate, //0
        Interval, //5
        CreateReport1, //1
        ReportType1, //8
        ReportFile1, //C:\Program Files (x86)\HostMonitor\Logs\dbf-full.dbf
        CreateReport2, //1
        ReportType2, //6
        ReportFile2, //C:\Program Files (x86)\HostMonitor\Logs\dbf-big.wml
        CreateReport3, //1
        ReportType3, //1
        ReportFile3, //C:\Program Files (x86)\HostMonitor\Logs\rep-admin.htm
        CreateReport4, //1
        ReportType4, //2
        ReportFile4, //C:\Program Files (x86)\HostMonitor\Logs\rep-man.htm
        CreateReport5, //1
        ReportType5, //3
        ReportFile5, //C:\Program Files (x86)\HostMonitor\Logs\rep-boss.htm
        CreateReport6, //1
        ReportType6, //4
        ReportFile6, //C:\Program Files (x86)\HostMonitor\Logs\rep-full.htm
        ExecuteActions, //0
        ActionsProfile, //-1
            //Misc(Reports)
        ShowFolders, //1
        SkipEmptyFolders, //0
        // Service
        Logon, //0
        User, //
        Pswd, // + //SMS_SMPP1 + //SMS_SMPP2
        Delay, //0
        SaveMode, //0 + Logging1 = 2 + Logging2 = 2
        //Misc
            //Preference
        StoreStatistics, //1
        StoreIterations, //1
            //Behavior
        DisableResetIterations, //0
        PauseResetIterations, //0
            //Misc(Reports)
        AliveDeadRatioMode, //0
            //Misc(ODBC)
        DoNotUse_SqlFetchAbsolute, //1
        ODBC_UseSystemDSN, //1
        ODBC_ConnectionPooling, //0
            //Misc(SSlOptions)
        sslAnyHostPOP3, //0
        sslAnyDatePOP3, //0
        sslAnyAuthPOP3, //0
        sslAnyHostIMAP, //0
        sslAnyDateIMAP, //0
        sslAnyAuthIMAP, //0
        sslAnyHostLDAP, //0
        sslAnyDateLDAP, //0
        sslAnyAuthLDAP, //0
            //Misc(Settings for URL)
        DefAgentName, //Mozilla/4.0 (compatible; MSIE 6.0)
        IGNORE_CERT_CN_INVALID, //0
        IGNORE_CERT_DATE_INVALID, //0
            //Misc(Settings for UNC)
        UNCRetries, //2
        UNCMode, //0
        UNCShowErrors, //0
            //Misc(NT Events Log)
        ShowNTEventDescr, //1
            //Misc (Performance Counter tests)
        PerfWorkMode, //0
        //FixedFormats
            //Misc(Date & Time)
        UseFixedFormats, //0
        FixedDateFormat, //MM/dd/yyyy
        FixedTimeFormat, //h:mm:ss AMPM
            //Misc(SNMP Get tests)
        snmpAutoSingleInstance, //0
            //Misc (Traffic monitor)
        TrafficMonitorUnits, //0
        //Interface
            //Preference
        SaveCurrFolder, //1
            //HTML Colors
        DefaultLogPaletteID, //6
        //Logging
            //Primary Log
        odbcLogSource, // + Logging2
        odbcLogUser, // + Logging2
        odbcLogPswd, // + Logging2
        odbcLogTimeout, //10 + Logging2 = 10
        odbcLogSQLQuer, // + Logging2  //Insert into hmlog (eventtime, testname, status, reply, testid, testmethod) VALUES ('%DateTime%', '%TestName%', '%Status%', '%Reply%', %TestID%, '%TestMethod%')
        odbcParam1, // + Logging2
            //SystemLog
        SysLogFileName, //C:\Program Files (x86)\HostMonitor\Logs\syslog.htm
        LogSuccessActions, //0
        LogFailedActions, //1
            //Log processing
        UseBothLogs, //0
            //Misc(RMA/Logging)
        LogStateChanges, //1
        RecordPrimaryRMAErrors, //1
        //Logging1
            //Primary Log
        File2Name, //C:\Program Files (x86)\HostMonitor\Logs\log%mmyyyy%.htm + Logging2 C:\Program Files (x86)\HostMonitor\Logs\log%mmyyyy%.txt
        LogFormat, //0 + Logging2 =
        Target, //1 + Logging2 = 0
        LogNameMethod, //0 + Logging2 = 0
        UseDeadAction, //0 + Logging2 = 0
        UseGoodAction, //0
        DeadActionID, //-1 + Logging2 = -1
        GoodActionID, //-1
        //Logging2
        //Logging_CommonProcessing
            //Log processing
        CheckEnabled, //0 + //Logging_PrivProcessing = 0
        CheckMode, //0 + //Logging_PrivProcessing = 1
        TimeUnit, //2 + //Logging_PrivProcessing = 2
        TimeLimit, //3 + //Logging_PrivProcessing = 3
        SizeLimit, //600000 + //Logging_PrivProcessing = 200000
        ExtCommand, //cmd  /c  del  "%log%" + //Logging_PrivProcessing = cmd  /c  move /y  "%log%"  "%logpath%old\%logname%"

        //ICQ
            //ICQ
        PrimaryUIN, //0
        BackupUIN, //0
        PrimaryPswd, // + //Jabber
        BackupPswd, // + //Jabber
        //GSM
            //GSM
        Primary_ComPort, //COM1
        Primary_BaudRate, //19200
        Primary_Modem, //A1
        Primary_SMSFormat, //0
        Primary_PIN, //1111
        Primary_SCA, //
        Backup_ComPort, //COM2
        Backup_BaudRate, //19200
        Backup_Modem, //Nokia6650
        Backup_SMSFormat, //0
        Backup_PIN, //1111
        Backup_SCA, //
        LogMode, //2NEVER
        LogFile, //C:\Program Files (x86)\HostMonitor\Logs\smslog.txt
        //UpdateCheck
            //Misc(UpdateCheck)
        AutoMode, //1
        //Jabber
            //Jabber
        PrimaryUserName, //
        PrimaryLoginServer, //jabber.org
        PrimaryLoginPort, //5222
        BackupUserName, //
        BackupLoginServer, //jabber.org
        BackupLoginPort, //5222
        PrimarySSLMode, //0
        BackupSSLMode, //0
        //SMS_SMPP1
        //SMS_SMPP2
            //SMS_SMPP
        Host, // + //SMS_SMPP2
        Port, //2775 + //SMS_SMPP2 = 2775 + //RCI =1054 + //Active RMA = 5056 + // Misc(SNMP trap test) =
        ID, // + //SMS_SMPP2 =
        TON, //0 + //SMS_SMPP2 = 0
        NPI, //0 + //SMS_SMPP2 = 0
        SrcAddr, // + //SMS_SMPP2 =
        //RCI
            //RCI
        Enabled, //0 + //Active RMA = 0
        MaxClients, //16
        LogSuccess, //1
        LogError, //1
        LogAccepted, //1 + //Active RMA = 0
        LogRejected, //1 + //Active RMA = 1
        LogAcceptedWatchDog, //0
        LogRejectedWatchDog, //1
        //Scheduler
        Mode1, //0
        Time1, //000000
        Interval1, //60
        Day1, //1
        SchedAlerts1, //-1
        ExecutedAt1, //30121899000000
        Mode2, //0
        Time2, //000000
        Interval2, //60
        Day2, //1
        SchedAlerts2, //-1
        ExecutedAt2, //30121899000000
        Mode3, //0
        Time3, //000000
        Interval3, //60
        Day3, //1
        SchedAlerts3, //-1
        ExecutedAt3, //30121899000000
        Mode4, //0
        Time4, //000000
        Interval4, //60
        Day4, //1
        SchedAlerts4, //-1
        ExecutedAt4, //30121899000000
        Mode5, //0
        Time5, //000000
        Interval5, //60
        Day5, //1
        SchedAlerts5, //-1
        ExecutedAt5, //30121899000000
        //TrapListener
            //Misc(SNMP Trap Test)
        TrafficCheck, //1
        TrafficLimit, //1800
        TrafficSpan, //60
        Pause, //1
        PauseSpan, //60
        Action, //0
        ActionID, //-1
        //ActiveRMAServer
            //Active RMA
        AcceptAnyIP, //1
        AcceptedList, //
        IPMarks, //


        //Logging_PrivProcessing


    };

    class ValueRef{
        public:
            ValueRef(Settings &st, const QString &kp) :
                parent(st), keyPath(kp){}
            ValueRef & operator = (const QVariant &d);
        private:
            Settings &parent;
            const QString keyPath;
    };

    static QVariant get(Section s, Key k, QVariant def);
    static ValueRef set(Section s, Key k);
    static void save();

private:
    QString keyPath(Section, Key);

    static Settings & instance();
    QMetaEnum keys;
    QMetaEnum sections;
    QSettings conf;

    Settings();
    Settings(const Settings &);
    Settings & operator = (const Settings &);
};

} // namespace SDPO

#endif // SETTINGS_H
