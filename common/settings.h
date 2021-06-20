#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#define ORGANIZATION_NAME "SNIIP"
#define ORGANIZATION_DOMAIN "sniip.ru"
#define APPLICATION_NAME "SDPO"

// HostMonitor
// IP_Monitor
// Environ
#define SKEY_PING_ClearOldInfo         "Environ/ClearOldInfo"
#define SVAL_PING_ClearOldInfo         0
#define SKEY_PING_ShowHostsDescription "Environ/ShowHostsDescription"
#define SVAL_PING_ShowHostsDescription 1

#define SKEY_PREF_FontName       "Environ/FontName"
#define SVAL_PREF_FontName       "DejaVu Sans"
#define SKEY_PREF_FontSize       "Environ/FontSize"
#define SVAL_PREF_FontSize       8
#define SKEY_PREF_TelnetFontName "Environ/TelnetFontName"
#define SVAL_PREF_TelnetFontName "Carlito"
#define SKEY_PREF_TelnetFontSize "Environ/TelnetFontSize"
#define SVAL_PREF_TelnetFontSize 12
#define SKEY_PREF_AutoSave       "Environ/AutoSave"
#define SVAL_PREF_AutoSave       1
#define SKEY_PREF_AutoSaveMode   "Environ/AutoSaveMode"
#define SVAL_PREF_AutoSaveMode   5
#define SKEY_PREF_KeptAddresses  "Environ/KeptAddresses"
#define SVAL_PREF_KeptAddresses  1
#define SKEY_PREF_DeepAddresses  "Environ/DeepAddresses"
#define SVAL_PREF_DeepAddresses  5
#define SKEY_PREF_MinToTray      "Environ/MinToTray"
#define SVAL_PREF_MinToTray      1
#define SKEY_PREF_AnimateIcon    "Environ/AnimateIcon"
#define SVAL_PREF_AnimateIcon    1
#define SKEY_PREF_ChangeIcon     "Environ/ChangeIcon"
#define SVAL_PREF_ChangeIcon     1
#define SKEY_PREF_StayFormTop    "Environ/StayFormTop"
#define SVAL_PREF_StayFormTop    0

#define SKEY_STARTUP_StartStopMode "Environ/StartStopMode"
#define SVAL_STARTUP_StartStopMode 2
#define SKEY_STARTUP_WinStatusMode "Environ/WinStatusMode"
#define SVAL_STARTUP_WinStatusMode 3
#define SKEY_STARTUP_FileLoadMode  "Environ/FileLoadMode"
#define SVAL_STARTUP_FileLoadMode  2
#define SKEY_STARTUP_ErrorHandlerMode "Environ/ErrorHandlerMode"
#define SVAL_STARTUP_ErrorHandlerMode 1
#define SKEY_STARTUP_LoadFileName  "Environ/LoadFileName"

#define SKEY_ENVIRON_DigitsAfterDotStat "Environ/DigitsAfterDotStat"
#define SVAL_ENVIRON_DigitsAfterDotStat 2

// Telnet,
// LogViewer
#define SKEY_LOGVIEWER_TextViewerMode "LogViewer/TextViewerMode"
#define SVAL_LOGVIEWER_TextViewerMode 0
#define SKEY_LOGVIEWER_HtmlViewerMode "LogViewer/HTMLViewerMode"
#define SVAL_LOGVIEWER_HtmlViewerMode 1
#define SKEY_LOGVIEWER_DbfViewerMode  "LogViewer/DBFViewerMode"
#define SVAL_LOGVIEWER_DbfViewerMode  0
#define SKEY_LOGVIEWER_TextViewerCmd  "LogViewer/TextViewerCmd"
#define SVAL_LOGVIEWER_TextViewerCmd  "notepad.exe %log%"
#define SKEY_LOGVIEWER_HtmlViewerCmd  "LogViewer/HTMLViewerCmd"
#define SKEY_LOGVIEWER_DbfViewerCmd   "LogViewer/DBFViewerCmd"

// Ping_Trace
#define SKEY_PING_Packets    "Ping_Trace/Packets"
#define SVAL_PING_Packets    1
#define SKEY_PING_PacketSize "Ping_Trace/PacketSize"
#define SVAL_PING_PacketSize 32
#define SKEY_PING_Timeout    "Ping_Trace/Timeout"
#define SVAL_PING_Timeout    1000
#define SKEY_PING_TTL        "Ping_Trace/TTL"
#define SVAL_PING_TTL        3
#define SKEY_PING_Hops       "Ping_Trace/Hops"
#define SVAL_PING_Hops       32
#define SKEY_PING_StopTrace  "Ping_Trace/StopTrace"
#define SVAL_PING_StopTrace  1

// Language,
// HostMon
#define SKEY_HOSTMON_MsgWinTime "HostMon/MsgWinTime"
#define SVAL_HOSTMON_MsgWinTime 5
#define SKEY_HOSTMON_MsgWinXPos "HostMon/MsgWinXPos"
#define SVAL_HOSTMON_MsgWinXPos 200
#define SKEY_HOSTMON_MsgWinYPos "HostMon/MsgWinYPos"
#define SVAL_HOSTMON_MsgWinYPos 100
#define SKEY_HOSTMON_MsgWinConstPos  "HostMon/MsgWinConstPos"
#define SVAL_HOSTMON_MsgWinConstPos  0
#define SKEY_HOSTMON_MsgWinCloseAuto "HostMon/MsgWinCloseAuto"
#define SVAL_HOSTMON_MsgWinCloseAuto 1
#define SKEY_HOSTMON_MsgWinStayTop "HostMon/MsgWinStayTop"
#define SVAL_HOSTMON_MsgWinStayTop 1
#define SKEY_HOSTMON_AccessMethod  "HostMon/AccessMethod"
#define SVAL_HOSTMON_AccessMethod  0

#define SKEY_HOSTMON_RefreshMode            "HostMon/RefreshMode"
#define SVAL_HOSTMON_RefreshMode            2
#define SKEY_HOSTMON_MaxThreads             "HostMon/MaxThreads"
#define SVAL_HOSTMON_MaxThreads             32
#define SKEY_HOSTMON_MastersLifetime        "HostMon/MastersLifetime"
#define SVAL_HOSTMON_MastersLifetime        60
#define SKEY_HOSTMON_RecheckDependants      "HostMon/RecheckDependants"
#define SVAL_HOSTMON_RecheckDependants      0
#define SKEY_HOSTMON_CommentForDisabling    "HostMon/CommentForDisabling"
#define SVAL_HOSTMON_CommentForDisabling    0
#define SKEY_HOSTMON_DisableResetIterations "HostMon/DisableResetIterations"
#define SVAL_HOSTMON_DisableResetIterations 0
#define SKEY_HOSTMON_PauseResetIterations   "HostMon/PauseResetIterations"
#define SVAL_HOSTMON_PauseResetIterations   0

#define SKEY_HOSTMON_CheckInternetConnection "HostMon/CheckInternetConnection"
#define SVAL_HOSTMON_CheckInternetConnection 0

#define SKEY_HOSTMON_StartupRun "HostMon/StartupRun"
#define SVAL_HOSTMON_StartupRun 0

// Proxy server
#define SKEY_PROXY_Server "HostMon/ProxyServer"
#define SVAL_PROXY_Server "127.0.0.1"
#define SKEY_PROXY_Port   "HostMon/ProxyPort"
#define SVAL_PROXY_Port   80
#define SKEY_PROXY_Auth   "HostMon/ProxyAut"
#define SVAL_PROXY_Auth   1
#define SKEY_PROXY_User   "HostMon/ProxyUser"
#define SVAL_PROXY_User   "test"
#define SKEY_PROXY_Pswd   "HostMon/ProxyPswd"
#define SKEY_PROXY_Param2 "HostMon/ProxyParam2"
#define SVAL_PROXY_Param2 "<local>;"

// SMTP
#define SKEY_SMTP_Server1 "SMTP/SMTPServer"
#define SVAL_SMTP_Server1 "smtp.mail.yahoo.com"
#define SKEY_SMTP_Port1 "SMTP/SMTPPort"
#define SVAL_SMTP_Port1 25
#define SKEY_SMTP_SslType1 "SMTP/SSLType1"
#define SVAL_SMTP_SslType1 0
#define SKEY_SMTP_Auth1 "SMTP/Authentication1"
#define SVAL_SMTP_Auth1 0
#define SKEY_SMTP_User1 "SMTP/Username1"
#define SKEY_SMTP_Pswd1 "SMTP/Password1"

#define SKEY_SMTP_Server2 "SMTP/SMTPServer2"
#define SVAL_SMTP_Server2 "smtp.mail.yahoo.com"
#define SKEY_SMTP_Port2 "SMTP/SMTPPort2"
#define SVAL_SMTP_Port2 25
#define SKEY_SMTP_SslType2 "SMTP/SSLType2"
#define SVAL_SMTP_SslType2 0
#define SKEY_SMTP_Auth2 "SMTP/Authentication2"
#define SVAL_SMTP_Auth2 0
#define SKEY_SMTP_User2 "SMTP/Username2"
#define SKEY_SMTP_Pswd2 "SMTP/Password2"

#define SKEY_SMTP_ShowMailWin "SMTP/ShowMailWin"
#define SVAL_SMTP_ShowMailWin 1
#define SKEY_SMTP_MailWinAutoClose "SMTP/MailWinAutoClose"
#define SVAL_SMTP_MailWinAutoClose 1
#define SKEY_SMTP_MailWinCloseAfter "SMTP/MailWinCloseAfter"
#define SVAL_SMTP_MailWinCloseAfter 6
#define SKEY_SMTP_ShowMailWinInLastPos "SMTP/ShowMailWinInLastPos"
#define SVAL_SMTP_ShowMailWinInLastPos 1

// LogViewers,
// TxtLogViewer,
// LogAnalizer,
// Pagers
#define SKEY_PAGERS_Device          "Pagers/pgDevice"
#define SVAL_PAGERS_Device          "Auto select free TAPI device"
#define SKEY_PAGERS_BoudRate        "Pagers/pgBoudRate"
#define SVAL_PAGERS_BoudRate        "2400"
#define SKEY_PAGERS_InitStr         "Pagers/pgInitStr"
#define SVAL_PAGERS_InitStr         "AUTO"
#define SKEY_PAGERS_DialStr         "Pagers/pgDialStr"
#define SVAL_PAGERS_DialStr         "ATDT"
#define SKEY_PAGERS_ShowWindow      "Pagers/pgShowWindow"
#define SVAL_PAGERS_ShowWindow      1
#define SKEY_PAGERS_CloseWindow     "Pagers/pgCloseWindow"
#define SVAL_PAGERS_CloseWindow     1
#define SKEY_PAGERS_CloseDelay      "Pagers/pgCloseDelay"
#define SVAL_PAGERS_CloseDelay      5
#define SKEY_PAGERS_WaitFreeDevice  "Pagers/pgWaitFreeDevice"
#define SVAL_PAGERS_WaitFreeDevice  1
#define SKEY_PAGERS_WaitDeviceDelay "Pagers/pgWaitDeviceDelay"
#define SVAL_PAGERS_WaitDeviceDelay 15

// Reports
#define SKEY_REPORTS_ShowFolders      "Reports/ShowFolders"
#define SVAL_REPORTS_ShowFolders      0
#define SKEY_REPORTS_SkipEmptyFolders "Reports/SkipEmptyFolders"
#define SVAL_REPORTS_SkipEmptyFolders 1

#define SKEY_REPORTS_AutoCreate "Reports/AutoCreate"
#define SVAL_REPORTS_AutoCreate 0
#define SKEY_REPORTS_Interval   "Reports/Interval"
#define SVAL_REPORTS_Interval   5

#define SKEY_REPORTS_CreateReport1 "Reports/CreateReport1"
#define SVAL_REPORTS_CreateReport1 1
#define SKEY_REPORTS_ReportType1   "Reports/ReportType1"
#define SVAL_REPORTS_ReportType1   8
#define SKEY_REPORTS_ReportFile1   "Reports/ReportFile1"
#define SVAL_REPORTS_ReportFile1   "dbf-full.dbf"

#define SKEY_REPORTS_CreateReport2 "Reports/CreateReport2"
#define SVAL_REPORTS_CreateReport2 1
#define SKEY_REPORTS_ReportType2   "Reports/ReportType2"
#define SVAL_REPORTS_ReportType2   6
#define SKEY_REPORTS_ReportFile2   "Reports/ReportFile2"
#define SVAL_REPORTS_ReportFile2   "dbf-big.dbf"

#define SKEY_REPORTS_CreateReport3 "Reports/CreateReport3"
#define SVAL_REPORTS_CreateReport3 1
#define SKEY_REPORTS_ReportType3   "Reports/ReportType3"
#define SVAL_REPORTS_ReportType3   1
#define SKEY_REPORTS_ReportFile3   "Reports/ReportFile3"
#define SVAL_REPORTS_ReportFile3   "rep-admin.htm"

#define SKEY_REPORTS_CreateReport4 "Reports/CreateReport4"
#define SVAL_REPORTS_CreateReport4 1
#define SKEY_REPORTS_ReportType4   "Reports/ReportType4"
#define SVAL_REPORTS_ReportType4   2
#define SKEY_REPORTS_ReportFile4   "Reports/ReportFile4"
#define SVAL_REPORTS_ReportFile4   "rep-man.htm"

#define SKEY_REPORTS_CreateReport5 "Reports/CreateReport5"
#define SVAL_REPORTS_CreateReport5 1
#define SKEY_REPORTS_ReportType5   "Reports/ReportType5"
#define SVAL_REPORTS_ReportType5   3
#define SKEY_REPORTS_ReportFile5   "Reports/ReportFile5"
#define SVAL_REPORTS_ReportFile5   "rep-boss.htm"

#define SKEY_REPORTS_CreateReport6 "Reports/CreateReport6"
#define SVAL_REPORTS_CreateReport6 1
#define SKEY_REPORTS_ReportType6   "Reports/ReportType6"
#define SVAL_REPORTS_ReportType6   4
#define SKEY_REPORTS_ReportFile6   "Reports/ReportFile6"
#define SVAL_REPORTS_ReportFile6   "rep-full.htm"

#define SKEY_REPORTS_ExecuteActions "Reports/ExecuteActions"
#define SVAL_REPORTS_ExecuteActions 0
#define SKEY_REPORTS_ActionsProfile "Reports/ActionsProfile"
#define SVAL_REPORTS_ActionsProfile -1

// Service
#define SKEY_SERVICE_Logon    "Service/Logon"
#define SVAL_SERVICE_Logon    1
#define SKEY_SERVICE_User     "Service/User"
#define SKEY_SERVICE_Pswd     "Service/Pswd"
#define SKEY_SERVICE_Delay    "Service/Delay"
#define SVAL_SERVICE_Delay    0
#define SKEY_SERVICE_SaveMode "Service/SaveMode"
#define SVAL_SERVICE_SaveMode 1

// Misc
#define SKEY_MISC_StoreStatistics "Misc/StoreStatistics"
#define SVAL_MISC_StoreStatistics 1
#define SKEY_MISC_StoreIterations "Misc/StoreIterations"
#define SVAL_MISC_StoreIterations 1

#define SKEY_MISC_AliveDeadRatioMode "Misc/AliveDeadRatioMode"
#define SVAL_MISC_AliveDeadRatioMode 0
#define SKEY_MISC_DoNotUseSqlFetchAbsolute "Misc/DoNotUse_SqlFetchAbsolute"
#define SVAL_MISC_DoNotUseSqlFetchAbsolute 1
#define SKEY_MISC_OdbcUseSystemDsn "Misc/ODBC_UseSystemDSN"
#define SVAL_MISC_OdbcUseSystemDsn 1
#define SKEY_MISC_OdbcConnectionPooling "Misc/ODBC_ConnectionPooling"
#define SVAL_MISC_OdbcConnectionPooling 0

// SSL options
#define SKEY_MISC_sslAnyHostPOP3 "Misc/sslAnyHostPOP3"
#define SVAL_MISC_sslAnyHostPOP3 0
#define SKEY_MISC_sslAnyDatePOP3 "Misc/sslAnyDatePOP3"
#define SVAL_MISC_sslAnyDatePOP3 0
#define SKEY_MISC_sslAnyAuthPOP3 "Misc/sslAnyAuthPOP3"
#define SVAL_MISC_sslAnyAuthPOP3 0
#define SKEY_MISC_sslAnyHostIMAP "Misc/sslAnyHostIMAP"
#define SVAL_MISC_sslAnyHostIMAP 0
#define SKEY_MISC_sslAnyDateIMAP "Misc/sslAnyDateIMAP"
#define SVAL_MISC_sslAnyDateIMAP 0
#define SKEY_MISC_sslAnyAuthIMAP "Misc/sslAnyAuthIMAP"
#define SVAL_MISC_sslAnyAuthIMAP 0
#define SKEY_MISC_sslAnyHostLDAP "Misc/sslAnyHostLDAP"
#define SVAL_MISC_sslAnyHostLDAP 0
#define SKEY_MISC_sslAnyDateLDAP "Misc/sslAnyDateLDAP"
#define SVAL_MISC_sslAnyDateLDAP 0
#define SKEY_MISC_sslAnyAuthLDAP "Misc/sslAnyAuthLDAP"
#define SVAL_MISC_sslAnyAuthLDAP 0

// Settings for URL tests
#define SKEY_MISC_DefAgentName "Misc/DefAgentName"
#define SVAL_MISC_DefAgentName "KharMonitor:/1.0"
#define SKEY_MISC_IgnoreCertCnInvalid "Misc/IGNORE_CERT_CN_INVALID"
#define SVAL_MISC_IgnoreCertCnInvalid 0
#define SKEY_MISC_IgnoreCertDateInvalid "Misc/IGNORE_CERT_DATE_INVALID"
#define SVAL_MISC_IgnoreCertDateInvalid 0

// Settings for UNC tests
#define SKEY_MISC_UncRetries "Misc/UNCRetries"
#define SVAL_MISC_UncRetries 2
#define SKEY_MISC_UncMode "Misc/UNCMode"
#define SVAL_MISC_UncMode 0
#define SKEY_MISC_UncShowErrors "Misc/UNCShowErrors"
#define SVAL_MISC_UncShowErrors 0

// NT event log tests
#define SKEY_MISC_ShowNTEventDescr "Misc/ShowNTEventDescr"
#define SVAL_MISC_ShowNTEventDescr 1

// Performance counter
#define SKEY_MISC_PerfWorkMode "Misc/PerfWorkMode"
#define SVAL_MISC_PerfWorkMode 0

// SNMP Get tests
#define SKEY_MISC_SnmpAutoSingleInstance "Misc/snmpAutoSingleInstance"
#define SVAL_MISC_SnmpAutoSingleInstance 0

// Traffic monitor tests
#define SKEY_MISC_TrafficMonitorUnits "Misc/TrafficMonitorUnits"
#define SVAL_MISC_TrafficMonitorUnits 0

// FixedFormats
#define SKEY_FF_UseFixedFormats "FixedFormats/UseFixedFormats"
#define SVAL_FF_UseFixedFormats 0
#define SKEY_FF_FixedDateFormat "FixedFormats/FixedDateFormat"
#define SVAL_FF_FixedDateFormat 3
#define SKEY_FF_FixedTimeFormat "FixedFormats/FixedTimeFormat"
#define SVAL_FF_FixedTimeFormat 0

// Interface
#define SKEY_INTERFACE_SaveCurrFolder "Interface/SaveCurrFolder"
#define SVAL_INTERFACE_SaveCurrFolder 1
#define SKEY_INTERFACE_DefaultLogPaletteID "Interface/DefaultLogPaletteID"
#define SVAL_INTERFACE_DefaultLogPaletteID "Grey"

// MonitorColumns,
// SortingColumns,
// RecentList1,
// Logging
#define SKEY_LOGGING_SysLogFileName    "Logging/SysLogFileName"
#define SKEY_LOGGING_LogSuccessActions "Logging/LogSuccessActions"
#define SVAL_LOGGING_LogSuccessActions 0
#define SKEY_LOGGING_LogFailedActions  "Logging/LogFailedActions"
#define SVAL_LOGGING_LogFailedActions  0

#define SKEY_LOGGING_RecordPrimaryRMAErrors  "Logging/RecordPrimaryRMAErrors"
#define SVAL_LOGGING_RecordPrimaryRMAErrors 1
#define SKEY_LOGGING_LogStateChanges "Logging/LogStateChanges"
#define SVAL_LOGGING_LogStateChanges 0

#define SKEY_LOGGING_UseBothLogs "Logging/UseBothLogs"
#define SVAL_LOGGING_UseBothLogs 0

#define SKEY_LOGGING_OdbcLogSource   "Logging/odbcLogSource"
#define SKEY_LOGGING_OdbcLogSqlQuery "Logging/odbcLogSQLQuer"
#define SVAL_LOGGING_OdbcLogSqlQuery "Insert into hmlog (eventtime, testname, status, reply, testid, testmethod) VALUES ('%DateTime%', '%TestName%', '%Status%', '%Reply%', %TestID%, '%TestMethod%')"
#define SKEY_LOGGING_OdbcLogUser     "Logging/odbcLogUser"
#define SKEY_LOGGING_OdbcLogPswd     "Logging/odbcLogPswd"
#define SKEY_LOGGING_OdbcLogTimeout  "Logging/odbcLogTimeout"
#define SVAL_LOGGING_OdbcLogTimeout  10

// Logging1
#define SKEY_LOG1_Target        "Logging1/Target"
#define SVAL_LOG1_Target        1
#define SKEY_LOG1_SaveMode      "Logging1/SaveMode"
#define SVAL_LOG1_SaveMode      2
#define SKEY_LOG1_LogNameMethod "Logging1/LogNameMethod"
#define SVAL_LOG1_LogNameMethod 0
#define SKEY_LOG1_File2Name     "Logging1/File2Name"
#define SKEY_LOG1_LogFormat     "Logging1/LogFormat"
#define SVAL_LOG1_LogFormat     0
#define SKEY_LOG1_UseDeadAction "Logging1/UseDeadAction"
#define SVAL_LOG1_UseDeadAction 0
#define SKEY_LOG1_DeadActionID  "Logging1/DeadActionID"
#define SVAL_LOG1_DeadActionID  -1
#define SKEY_LOG1_UseGoodAction "Logging1/UseGoodAction"
#define SVAL_LOG1_UseGoodAction 0
#define SKEY_LOG1_GoodActionID  "Logging1/GoodActionID"
#define SVAL_LOG1_GoodActionID  -1

// Logging2
#define SKEY_LOG2_Target "Logging2/Target"
#define SVAL_LOG2_Target 1
#define SKEY_LOG2_SaveMode "Logging2/SaveMode"
#define SVAL_LOG2_SaveMode 2
#define SKEY_LOG2_LogNameMethod "Logging2/LogNameMethod"
#define SVAL_LOG2_LogNameMethod 0
#define SKEY_LOG2_File2Name "Logging2/File2Name"
#define SKEY_LOG2_LogFormat "Logging2/LogFormat"
#define SVAL_LOG2_LogFormat 0
#define SKEY_LOG2_UseDeadAction "Logging2/UseDeadAction"
#define SVAL_LOG2_UseDeadAction 0
#define SKEY_LOG2_DeadActionID "Logging2/DeadActionID"
#define SVAL_LOG2_DeadActionID -1
#define SKEY_LOG2_OdbcLogSource "Logging2/odbcLogSource"
#define SKEY_LOG2_OdbcLogSqlQuery "Logging2/odbcLogSQLQuer"
#define SKEY_LOG2_OdbcLogUser "Logging2/odbcLogUser"
#define SKEY_LOG2_OdbcLogPswd "Logging2/odbcLogPswd"
#define SKEY_LOG2_OdbcLogTimeout "Logging2/odbcLogTimeout"
#define SVAL_LOG2_OdbcLogTimeout 10

// Logging_CommonProcessing
#define SKEY_COMMONLOG_CheckEnabled "Logging_CommonProcessing/CheckEnabled"
#define SVAL_COMMONLOG_CheckEnabled 0
#define SKEY_COMMONLOG_CheckMode    "Logging_CommonProcessing/CheckMode"
#define SVAL_COMMONLOG_CheckMode    0
#define SKEY_COMMONLOG_TimeUnit     "Logging_CommonProcessing/TimeUnit"
#define SVAL_COMMONLOG_TimeUnit     2
#define SKEY_COMMONLOG_TimeLimit    "Logging_CommonProcessing/TimeLimit"
#define SVAL_COMMONLOG_TimeLimit    3
#define SKEY_COMMONLOG_SizeLimit    "Logging_CommonProcessing/SizeLimit"
#define SVAL_COMMONLOG_SizeLimit    600000
#define SKEY_COMMONLOG_ExtCommand   "Logging_CommonProcessing/ExtCommand"
#define SVAL_COMMONLOG_ExtCommand   "cmd /c del \"%log%\" +"

// Logging_PrivProcessing
#define SKEY_PRIVLOG_CheckEnabled "Logging_PrivProcessing/CheckEnabled"
#define SVAL_PRIVLOG_CheckEnabled 0
#define SKEY_PRIVLOG_CheckMode    "Logging_PrivProcessing/CheckMode"
#define SVAL_PRIVLOG_CheckMode    1
#define SKEY_PRIVLOG_TimeUnit     "Logging_PrivProcessing/TimeUnit"
#define SVAL_PRIVLOG_TimeUnit     2
#define SKEY_PRIVLOG_TimeLimit    "Logging_PrivProcessing/TimeLimit"
#define SVAL_PRIVLOG_TimeLimit    3
#define SKEY_PRIVLOG_SizeLimit    "Logging_PrivProcessing/SizeLimit"
#define SVAL_PRIVLOG_SizeLimit    200000
#define SKEY_PRIVLOG_ExtCommand   "Logging_PrivProcessing/ExtCommand"
#define SVAL_PRIVLOG_ExtCommand   "cmd /c move /y \"%log%\" \"%logpath%old\%logname%\""

// ICQ
#define SKEY_ICQ_PrimaryUIN  "ICQ/PrimaryUIN"
#define SKEY_ICQ_PrimaryPswd "ICQ/PrimaryPswd"
#define SKEY_ICQ_BackupUIN   "ICQ/BackupUIN"
#define SKEY_ICQ_BackupPswd  "ICQ/BackupPswd"

// UpdateCheck
#define SKEY_UPDATE_AutoMode "UpdateCheck/AutoMode"
#define SVAL_UPDATE_AutoMode 1

// GSM
#define SKEY_GSM_PrimaryComPort   "GSM/Primary_ComPort"
#define SVAL_GSM_PrimaryComPort   "COM1"
#define SKEY_GSM_PrimaryBaudRate  "GSM/Primary_BaudRate"
#define SVAL_GSM_PrimaryBaudRate  "19200"
#define SKEY_GSM_PrimaryModem     "GSM/Primary_Modem"
#define SVAL_GSM_PrimaryModem     "Siemens A1"
#define SKEY_GSM_PrimarySmsFormat "GSM/Primary_SMSFormat"
#define SVAL_GSM_PrimarySmsFormat "PDU"
#define SKEY_GSM_PrimaryPIN       "GSM/Primary_PIN"
#define SVAL_GSM_PrimaryPIN       "1111"
#define SKEY_GSM_PrimarySCA       "GSM/Primary_SCA"

#define SKEY_GSM_BackupComPort   "GSM/Backup_ComPort"
#define SVAL_GSM_BackupComPort   "COM2"
#define SKEY_GSM_BackupBaudRate  "GSM/Backup_BaudRate"
#define SVAL_GSM_BackupBaudRate  "19200"
#define SKEY_GSM_BackupModem     "GSM/Backup_Modem"
#define SVAL_GSM_BackupModem     "Nokia 6650"
#define SKEY_GSM_BackupSmsFormat "GSM/Backup_SMSFormat"
#define SVAL_GSM_BackupSmsFormat "PDU"
#define SKEY_GSM_BackupPIN       "GSM/Backup_PIN"
#define SVAL_GSM_BackupPIN       "1111"
#define SKEY_GSM_BackupSCA       "GSM/Backup_SCA"

#define SKEY_GSM_LogMode "GSM/LogMode"
#define SVAL_GSM_LogMode 2
#define SKEY_GSM_LogFile "GSM/LogFile"
#define SVAL_GSM_LogFile "/logs/smslog.txt"

// Jabber
#define SKEY_JABBER_PrimaryLoginServer "Jabber/PrimaryLoginServer"
#define SVAL_JABBER_PrimaryLoginServer "jabber.org"
#define SKEY_JABBER_PrimaryUserName    "Jabber/PrimaryUserName"
#define SKEY_JABBER_PrimaryPswd        "Jabber/PrimaryPswd"
#define SKEY_JABBER_PrimarySslMode     "Jabber/PrimarySSLMode"
#define SVAL_JABBER_PrimarySslMode     0
#define SKEY_JABBER_PrimaryLoginPort   "Jabber/PrimaryLoginPort"
#define SVAL_JABBER_PrimaryLoginPort   5222

#define SKEY_JABBER_BackupLoginServer  "Jabber/BackupLoginServer"
#define SVAL_JABBER_BackupLoginServer  "jabber.org"
#define SKEY_JABBER_BackupUserName     "Jabber/BackupUserName"
#define SKEY_JABBER_BackupPswd         "Jabber/BackupPswd"
#define SKEY_JABBER_BackupSslMode      "Jabber/BackupSSLMode"
#define SVAL_JABBER_BackupSslMode      0
#define SKEY_JABBER_BackupLoginPort    "Jabber/BackupLoginPort"
#define SVAL_JABBER_BackupLoginPort    5222

// SMS_SMPP1
#define SKEY_SMSSMPP1_Host    "SMS_SMPP1/Host"
#define SKEY_SMSSMPP1_Port    "SMS_SMPP1/Port"
#define SVAL_SMSSMPP1_Port    2775
#define SKEY_SMSSMPP1_ID      "SMS_SMPP1/ID"
#define SKEY_SMSSMPP1_Pswd    "SMS_SMPP1/Pswd"
#define SKEY_SMSSMPP1_SrcAddr "SMS_SMPP1/SrcAddr"
#define SKEY_SMSSMPP1_TON     "SMS_SMPP1/TON"
#define SVAL_SMSSMPP1_TON     0
#define SKEY_SMSSMPP1_NPI     "SMS_SMPP1/NPI"
#define SVAL_SMSSMPP1_NPI     1

// SMS_SMPP2
#define SKEY_SMSSMPP2_Host    "SMS_SMPP2/Host"
#define SKEY_SMSSMPP2_Port    "SMS_SMPP2/Port"
#define SVAL_SMSSMPP2_Port    2775
#define SKEY_SMSSMPP2_ID      "SMS_SMPP2/ID"
#define SKEY_SMSSMPP2_Pswd    "SMS_SMPP2/Pswd"
#define SKEY_SMSSMPP2_SrcAddr "SMS_SMPP2/SrcAddr"
#define SKEY_SMSSMPP2_TON     "SMS_SMPP2/TON"
#define SVAL_SMSSMPP2_TON     0
#define SKEY_SMSSMPP2_NPI     "SMS_SMPP2/NPI"
#define SVAL_SMSSMPP2_NPI     1

// RCI
#define SKEY_RCI_Enabled             "RCI/Enabled"
#define SVAL_RCI_Enabled             0
#define SKEY_RCI_Port                "RCI/Port"
#define SVAL_RCI_Port                1054
#define SKEY_RCI_MaxClients          "RCI/MaxClients"
#define SVAL_RCI_MaxClients          16
#define SKEY_RCI_Timeout             "RCI/Timeout"
#define SVAL_RCI_Timeout             300
#define SKEY_RCI_LogAccepted         "RCI/LogAccepted"
#define SVAL_RCI_LogAccepted         1
#define SKEY_RCI_LogAcceptedWatchDog "RCI/LogAcceptedWatchDog"
#define SVAL_RCI_LogAcceptedWatchDog 1
#define SKEY_RCI_LogRejected         "RCI/LogRejected"
#define SVAL_RCI_LogRejected         1
#define SKEY_RCI_LogRejectedWatchDog "RCI/LogRejectedWatchDog"
#define SVAl_RCI_LogRejectedWatchDog 0
#define SKEY_RCI_LogSuccess          "RCI/LogSuccess"
#define SVAL_RCI_LogSuccess          1
#define SKEY_RCI_LogError            "RCI/LogError"
#define SVAL_RCI_LogError            1

// Scheduler
#define SKEY_SCHEDULER_Mode1        "Scheduler/Mode1"
#define SVAL_SCHEDULER_Mode1        0
#define SKEY_SCHEDULER_Time1        "Scheduler/Time1"
#define SKEY_SCHEDULER_Interval1    "Scheduler/Interval1"
#define SVAL_SCHEDULER_Interval1    60
#define SKEY_SCHEDULER_Day1         "Scheduler/Day1"
#define SVAL_SCHEDULER_Day1         1
#define SKEY_SCHEDULER_SchedAlerts1 "Scheduler/SchedAlerts1"
#define SVAL_SCHEDULER_SchedAlerts1 -1

#define SKEY_SCHEDULER_Mode2        "Scheduler/Mode2"
#define SVAL_SCHEDULER_Mode2        0
#define SKEY_SCHEDULER_Time2        "Scheduler/Time2"
#define SKEY_SCHEDULER_Interval2    "Scheduler/Interval2"
#define SVAL_SCHEDULER_Interval2    60
#define SKEY_SCHEDULER_Day2         "Scheduler/Day2"
#define SVAL_SCHEDULER_Day2         2
#define SKEY_SCHEDULER_SchedAlerts2 "Scheduler/SchedAlerts2"
#define SVAL_SCHEDULER_SchedAlerts2 -1

#define SKEY_SCHEDULER_Mode3        "Scheduler/Mode3"
#define SVAL_SCHEDULER_Mode3        0
#define SKEY_SCHEDULER_Time3        "Scheduler/Time3"
#define SKEY_SCHEDULER_Interval3    "Scheduler/Interval3"
#define SVAL_SCHEDULER_Interval3    60
#define SKEY_SCHEDULER_Day3         "Scheduler/Day3"
#define SVAL_SCHEDULER_Day3         3
#define SKEY_SCHEDULER_SchedAlerts3 "Scheduler/SchedAlerts3"
#define SVAL_SCHEDULER_SchedAlerts3 -1

#define SKEY_SCHEDULER_Mode4        "Scheduler/Mode4"
#define SVAL_SCHEDULER_Mode4        0
#define SKEY_SCHEDULER_Time4        "Scheduler/Time4"
#define SKEY_SCHEDULER_Interval4    "Scheduler/Interval4"
#define SVAL_SCHEDULER_Interval4    60
#define SKEY_SCHEDULER_Day4         "Scheduler/Day4"
#define SVAL_SCHEDULER_Day4         4
#define SKEY_SCHEDULER_SchedAlerts4 "Scheduler/SchedAlerts4"
#define SVAL_SCHEDULER_SchedAlerts4 -1

#define SKEY_SCHEDULER_Mode5        "Scheduler/Mode5"
#define SVAL_SCHEDULER_Mode5        0
#define SKEY_SCHEDULER_Time5        "Scheduler/Time5"
#define SKEY_SCHEDULER_Interval5    "Scheduler/Interval5"
#define SVAL_SCHEDULER_Interval5    60
#define SKEY_SCHEDULER_Day5         "Scheduler/Day5"
#define SVAL_SCHEDULER_Day5         5
#define SKEY_SCHEDULER_SchedAlerts5 "Scheduler/SchedAlerts5"
#define SVAL_SCHEDULER_SchedAlerts5 -1

// SNMP Trap Listener
#define SKEY_TRAP_Port "TrapListener/Port"
#define SVAL_TRAP_Port 162
#define SKEY_TRAP_TrafficCheck "TrapListener/TrafficCheck"
#define SVAL_TRAP_TrafficCheck 1
#define SKEY_TRAP_TrafficLimit "TrapListener/TrafficLimit"
#define SVAL_TRAP_TrafficLimit 1800
#define SKEY_TRAP_TrafficSpan  "TrapListener/TrafficSpan"
#define SVAL_TRAP_TrafficSpan  60
#define SKEY_TRAP_Pause "TrapListener/Pause"
#define SVAL_TRAP_Pause 1
#define SKEY_TRAP_PauseSpan "TrapListener/PauseSpan"
#define SVAL_TRAP_PauseSpan 60
#define SKEY_TRAP_Action "TrapListener/Action"
#define SVAL_TRAP_Action 1
#define SKEY_TRAP_ActionID "TrapListener/ActionID"
#define SVAL_TRAP_ActionID 0

// ActiveRMAServer
#define SKEY_RMA_Enabled     "ActiveRMAServer/Enabled"
#define SVAL_RMA_Enabled     0
#define SKEY_RMA_Port        "ActiveRMAServer/Port"
#define SVAL_RMA_Port        5056
#define SKEY_RMA_AcceptAnyIP "ActiveRMAServer/AcceptAnyIP"
#define SVAL_RMA_AcceptAnyIP 1
#define SKEY_RMA_LogAccepted "ActiveRMAServer/LogAccepted"
#define SVAL_RMA_LogAccepted 0
#define SKEY_RMA_LogRejected "ActiveRMAServer/LogRejected"
#define SVAL_RMA_LogRejected 0

#endif // SETTINGS_H
