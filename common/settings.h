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
#define SKEY_PING_ShowHostsDescription "Environ/ShowHostsDescription"

#define SKEY_PREF_FontName       "Environ/FontName"
#define SKEY_PREF_FontSize       "Environ/FontSize"
#define SKEY_PREF_TelnetFontName "Environ/TelnetFontName"
#define SKEY_PREF_TelnetFontSize "Environ/TelnetFontSize"
#define SKEY_PREF_AutoSave       "Environ/AutoSave"
#define SKEY_PREF_MinToTray      "Environ/MinToTray"
#define SKEY_PREF_StayFormTop    "Environ/StayFormTop"
#define SKEY_PREF_KeptAddresses  "Environ/KeptAddresses"
#define SKEY_PREF_DeepAddresses  "Environ/DeepAddresses"
#define SKEY_PREF_AnimateIcon    "Environ/AnimateIcon"
#define SKEY_PREF_ChangeIcon     "Environ/ChangeIcon"
#define SKEY_PREF_AutoSaveMode   "Environ/AutoSaveMode"

#define SKEY_STARTUP_StartStopMode    "Environ/StartStopMode"
#define SKEY_STARTUP_WinStatusMode    "Environ/WinStatusMode"
#define SKEY_STARTUP_FileLoadMode     "Environ/FileLoadMode"
#define SKEY_STARTUP_ErrorHandlerMode "Environ/ErrorHandlerMode"
#define SKEY_STARTUP_LoadFileName     "Environ/LoadFileName"

#define SKEY_ENVIRON_DigitsAfterDotStat "Environ/DigitsAfterDotStat"

// Telnet,
// LogViewer
#define SKEY_LOGVIEWER_TextViewerMode "LogViewer/TextViewerMode"
#define SKEY_LOGVIEWER_HtmlViewerMode "LogViewer/HTMLViewerMode"
#define SKEY_LOGVIEWER_DbfViewerMode  "LogViewer/DBFViewerMode"
#define SKEY_LOGVIEWER_TextViewerCmd  "LogViewer/TextViewerCmd"
#define SKEY_LOGVIEWER_HtmlViewerCmd  "LogViewer/HTMLViewerCmd"
#define SKEY_LOGVIEWER_DbfViewerCmd   "LogViewer/DBFViewerCmd"

// Ping_Trace
#define SKEY_PING_Packets    "Ping_Trace/Packets"
#define SKEY_PING_PacketSize "Ping_Trace/PacketSize"
#define SKEY_PING_Timeout    "Ping_Trace/Timeout"
#define SKEY_PING_TTL        "Ping_Trace/TTL"
#define SKEY_PING_Hops       "Ping_Trace/Hops"
#define SKEY_PING_StopTrace  "Ping_Trace/StopTrace"

// Language,
// HostMon
#define SKEY_HOSTMON_MsgWinTime          "HostMon/MsgWinTime"
#define SKEY_HOSTMON_MsgWinXPos          "HostMon/MsgWinXPos"
#define SKEY_HOSTMON_MsgWinYPos          "HostMon/MsgWinYPos"
#define SKEY_HOSTMON_MsgWinConstPos      "HostMon/MsgWinConstPos"
#define SKEY_HOSTMON_MsgWinCloseAuto     "HostMon/MsgWinCloseAuto"
#define SKEY_HOSTMON_MsgWinStayTop       "HostMon/MsgWinStayTop"
#define SKEY_HOSTMON_AccessMethod        "HostMon/AccessMethod"

#define SKEY_HOSTMON_RefreshMode            "HostMon/RefreshMode"
#define SKEY_HOSTMON_MaxThreads             "HostMon/MaxThreads"
#define SKEY_HOSTMON_MastersLifetime        "HostMon/MastersLifetime"
#define SKEY_HOSTMON_RecheckDependants      "HostMon/RecheckDependants"
#define SKEY_HOSTMON_CommentForDisabling    "HostMon/CommentForDisabling"
#define SKEY_HOSTMON_DisableResetIterations "HostMon/DisableResetIterations"
#define SKEY_HOSTMON_PauseResetIterations   "HostMon/PauseResetIterations"

#define SKEY_HOSTMON_CheckInternetConnection "HostMon/CheckInternetConnection"

#define SKEY_STARTUP_StartupRun "HostMon/StartupRun"

#define SKEY_PROXY_Server "HostMon/ProxyServer"
#define SKEY_PROXY_Port   "HostMon/ProxyPort"
#define SKEY_PROXY_Auth   "HostMon/ProxyAut"
#define SKEY_PROXY_User   "HostMon/ProxyUser"
#define SKEY_PROXY_Pswd   "HostMon/ProxyPswd"
#define SKEY_PROXY_Param2 "HostMon/ProxyParam2"

// SMTP
#define SKEY_SMTP_Server1  "SMTP/SMTPServer"
#define SKEY_SMTP_Port1    "SMTP/SMTPPort"
#define SKEY_SMTP_SslType1 "SMTP/SSLType1"
#define SKEY_SMTP_Auth1    "SMTP/Authentication1"
#define SKEY_SMTP_User1    "SMTP/Username1"
#define SKEY_SMTP_Pswd1    "SMTP/Password1"

#define SKEY_SMTP_Server2  "SMTP/SMTPServer2"
#define SKEY_SMTP_Port2    "SMTP/SMTPPort2"
#define SKEY_SMTP_SslType2 "SMTP/SSLType2"
#define SKEY_SMTP_Auth2    "SMTP/Authentication2"
#define SKEY_SMTP_User2    "SMTP/Username2"
#define SKEY_SMTP_Pswd2    "SMTP/Password2"

#define SKEY_SMTP_ShowMailWin          "SMTP/ShowMailWin"
#define SKEY_SMTP_MailWinAutoClose     "SMTP/MailWinAutoClose"
#define SKEY_SMTP_MailWinCloseAfter    "SMTP/MailWinCloseAfter"
#define SKEY_SMTP_ShowMailWinInLastPos "SMTP/ShowMailWinInLastPos"

// LogViewers,
// TxtLogViewer,
// LogAnalizer,
// Pagers
#define SKEY_PAGERS_Device          "Pagers/pgDevice"
#define SKEY_PAGERS_BoudRate        "Pagers/pgBoudRate"
#define SKEY_PAGERS_InitStr         "Pagers/pgInitStr"
#define SKEY_PAGERS_DialStr         "Pagers/pgDialStr"
#define SKEY_PAGERS_ShowWindow      "Pagers/pgShowWindow"
#define SKEY_PAGERS_ClodeWindow     "Pagers/pgCloseWindow"
#define SKEY_PAGERS_CloseDelay      "Pagers/pgCloseDelay"
#define SKEY_PAGERS_WaitFreeDevice  "Pagers/pgWaitFreeDevice"
#define SKEY_PAGERS_WaitDeviceDelay "Pagers/pgWaitDeviceDelay"

// Reports
#define SKEY_REPORTS_ShowFolders      "Reports/ShowFolders"
#define SKEY_REPORTS_SkipEmptyFolders "Reports/SkipEmptyFolders"

#define SKEY_REPORTS_AutoCreate     "Reports/AutoCreate"
#define SKEY_REPORTS_Interval       "Reports/Interval"
#define SKEY_REPORTS_CreateReport1  "Reports/CreateReport1"
#define SKEY_REPORTS_ReportType1    "Reports/ReportType1"
#define SKEY_REPORTS_ReportFile1    "Reports/ReportFile1"
#define SKEY_REPORTS_CreateReport2  "Reports/CreateReport2"
#define SKEY_REPORTS_ReportType2    "Reports/ReportType2"
#define SKEY_REPORTS_ReportFile2    "Reports/ReportFile2"
#define SKEY_REPORTS_CreateReport3  "Reports/CreateReport3"
#define SKEY_REPORTS_ReportType3    "Reports/ReportType3"
#define SKEY_REPORTS_ReportFile3    "Reports/ReportFile3"
#define SKEY_REPORTS_CreateReport4  "Reports/CreateReport4"
#define SKEY_REPORTS_ReportType4    "Reports/ReportType4"
#define SKEY_REPORTS_ReportFile4    "Reports/ReportFile4"
#define SKEY_REPORTS_CreateReport5  "Reports/CreateReport5"
#define SKEY_REPORTS_ReportType5    "Reports/ReportType5"
#define SKEY_REPORTS_ReportFile5    "Reports/ReportFile5"
#define SKEY_REPORTS_CreateReport6  "Reports/CreateReport6"
#define SKEY_REPORTS_ReportType6    "Reports/ReportType6"
#define SKEY_REPORTS_ReportFile6    "Reports/ReportFile6"
#define SKEY_REPORTS_ExecuteActions "Reports/ExecuteActions"
#define SKEY_REPORTS_ActionsProfile "Reports/ActionsProfile"

// Service
#define SKEY_SERVICE_Logon    "Service/Logon"
#define SKEY_SERVICE_User     "Service/User"
#define SKEY_SERVICE_Pswd     "Service/Pswd"
#define SKEY_SERVICE_Delay    "Service/Delay"
#define SKEY_SERVICE_SaveMode "Service/SaveMode"

// Misc
#define SKEY_MISC_StoreIterations          "Misc/StoreIterations"
#define SKEY_MISC_StoreStatistics          "Misc/StoreStatistics"

#define SKEY_MISC_AliveDeadRatioMode       "Misc/AliveDeadRatioMode"
#define SKEY_MISC_DoNotUseSqlFetchAbsolute "Misc/DoNotUse_SqlFetchAbsolute"
#define SKEY_MISC_OdbcUseSystemDsn         "Misc/ODBC_UseSystemDSN"
#define SKEY_MISC_OdbcConnectionPooling    "Misc/ODBC_ConnectionPooling"

#define SKEY_MISC_sslAnyHostPOP3 "Misc/sslAnyHostPOP3"
#define SKEY_MISC_sslAnyDatePOP3 "Misc/sslAnyDatePOP3"
#define SKEY_MISC_sslAnyAuthPOP3 "Misc/sslAnyAuthPOP3"
#define SKEY_MISC_sslAnyHostIMAP "Misc/sslAnyHostIMAP"
#define SKEY_MISC_sslAnyDateIMAP "Misc/sslAnyDateIMAP"
#define SKEY_MISC_sslAnyAuthIMAP "Misc/sslAnyAuthIMAP"
#define SKEY_MISC_sslAnyHostLDAP "Misc/sslAnyHostLDAP"
#define SKEY_MISC_sslAnyDateLDAP "Misc/sslAnyDateLDAP"
#define SKEY_MISC_sslAnyAuthLDAP "Misc/sslAnyAuthLDAP"

#define SKEY_MISC_DefAgentName          "Misc/DefAgentName"
#define SKEY_MISC_IgnoreCertCnInvalid   "Misc/IGNORE_CERT_CN_INVALID"
#define SKEY_MISC_IgnoreCertDateInvalid "Misc/IGNORE_CERT_DATE_INVALID"

#define SKEY_MISC_UncRetries    "Misc/UNCRetries"
#define SKEY_MISC_UncMode       "Misc/UNCMode"
#define SKEY_MISC_UncShowErrors "Misc/UNCShowErrors"

#define SKEY_MISC_ShowNTEventDescr "Misc/ShowNTEventDescr"

#define SKEY_MISC_PerfWorkMode "Misc/PerfWorkMode"

#define SKEY_MISC_SnmpAutoSingleInstance "Misc/snmpAutoSingleInstance"

#define SKEY_MISC_TrafficMonitorUnits "Misc/TrafficMonitorUnits"

// FixedFormats
#define SKEY_FORMATS_UseFixedFormats "FixedFormats/UseFixedFormats"
#define SKEY_FORMATS_FixedDateFormat "FixedFormats/FixedDateFormat"
#define SKEY_FORMATS_FixedTimeFormat "FixedFormats/FixedTimeFormat"

// Interface
#define SKEY_INTERFACE_SaveCurrFolder      "Interface/SaveCurrFolder"
#define SKEY_INTERFACE_DefaultLogPaletteID "Interface/DefaultLogPaletteID"

// MonitorColumns,
// SortingColumns,
// RecentList1,
// Logging
#define SKEY_LOGGING_SysLogFileName    "Logging/SysLogFileName"
#define SKEY_LOGGING_LogSuccessActions "Logging/LogSuccessActions"
#define SKEY_LOGGING_LogFailedActions  "Logging/LogFailedActions"

#define SKEY_LOGGING_RecordPrimaryRMAErrors  "Logging/RecordPrimaryRMAErrors"
#define SKEY_LOGGING_LogStateChanges         "Logging/LogStateChanges"

#define SKEY_LOGGING_UseBothLogs         "Logging/UseBothLogs"

#define SKEY_LOGGING_OdbcLogSource   "Logging/odbcLogSource"
#define SKEY_LOGGING_OdbcLogSqlQuery "Logging/odbcLogSQLQuer"
#define SKEY_LOGGING_OdbcLogUser     "Logging/odbcLogUser"
#define SKEY_LOGGING_OdbcLogPswd     "Logging/odbcLogPswd"
#define SKEY_LOGGING_OdbcLogTimeout  "Logging/odbcLogTimeout"

#define SVAL_LOGGING_OdbcQuery "Insert into hmlog (eventtime, testname, status, reply, testid, testmethod) VALUES ('%DateTime%', '%TestName%', '%Status%', '%Reply%', %TestID%, '%TestMethod%')"

// Logging1
#define SKEY_LOG1_Target          "Logging1/Target"
#define SKEY_LOG1_SaveMode        "Logging1/SaveMode"
#define SKEY_LOG1_LogNameMethod   "Logging1/LogNameMethod"
#define SKEY_LOG1_File2Name       "Logging1/File2Name"
#define SKEY_LOG1_LogFormat       "Logging1/LogFormat"
#define SKEY_LOG1_UseDeadAction   "Logging1/UseDeadAction"
#define SKEY_LOG1_DeadActionID    "Logging1/DeadActionID"
#define SKEY_LOG1_UseGoodAction   "Logging1/UseGoodAction"
#define SKEY_LOG1_GoodActionID    "Logging1/GoodActionID"

// Logging2
#define SKEY_LOG2_Target          "Logging2/Target"
#define SKEY_LOG2_SaveMode        "Logging2/SaveMode"
#define SKEY_LOG2_LogNameMethod   "Logging2/LogNameMethod"
#define SKEY_LOG2_File2Name       "Logging2/File2Name"
#define SKEY_LOG2_LogFormat       "Logging2/LogFormat"
#define SKEY_LOG2_UseDeadAction   "Logging2/UseDeadAction"
#define SKEY_LOG2_DeadActionID    "Logging2/DeadActionID"
#define SKEY_LOG2_OdbcLogSource   "Logging2/odbcLogSource"
#define SKEY_LOG2_OdbcLogSqlQuery "Logging2/odbcLogSQLQuer"
#define SKEY_LOG2_OdbcLogUser     "Logging2/odbcLogUser"
#define SKEY_LOG2_OdbcLogPswd     "Logging2/odbcLogPswd"
#define SKEY_LOG2_OdbcLogTimeout  "Logging2/odbcLogTimeout"

// Logging_CommonProcessing
#define SKEY_COMMONLOG_CheckEnabled "Logging_CommonProcessing/CheckEnabled"
#define SKEY_COMMONLOG_CheckMode    "Logging_CommonProcessing/CheckMode"
#define SKEY_COMMONLOG_TimeUnit     "Logging_CommonProcessing/TimeUnit"
#define SKEY_COMMONLOG_TimeLimit    "Logging_CommonProcessing/TimeLimit"
#define SKEY_COMMONLOG_SizeLimit    "Logging_CommonProcessing/SizeLimit"
#define SKEY_COMMONLOG_ExtCommand   "Logging_CommonProcessing/ExtCommand"

// Logging_PrivProcessing
#define SKEY_PRIVLOG_CheckEnabled "Logging_PrivProcessing/CheckEnabled"
#define SKEY_PRIVLOG_CheckMode    "Logging_PrivProcessing/CheckMode"
#define SKEY_PRIVLOG_TimeUnit     "Logging_PrivProcessing/TimeUnit"
#define SKEY_PRIVLOG_TimeLimit    "Logging_PrivProcessing/TimeLimit"
#define SKEY_PRIVLOG_SizeLimit    "Logging_PrivProcessing/SizeLimit"
#define SKEY_PRIVLOG_ExtCommand   "Logging_PrivProcessing/ExtCommand"

// ICQ
#define SKEY_ICQ_PrimaryUIN  "ICQ/PrimaryUIN"
#define SKEY_ICQ_PrimaryPswd "ICQ/PrimaryPswd"
#define SKEY_ICQ_BackupUIN   "ICQ/BackupUIN"
#define SKEY_ICQ_BackupPswd  "ICQ/BackupPswd"

// UpdateCheck
#define SKEY_UPDATE_AutoMode "UpdateCheck/AutoMode"

// GSM
#define SKEY_GSM_PrimaryComPort   "GSM/Primary_ComPort"
#define SKEY_GSM_PrimaryBaudRate  "GSM/Primary_BaudRate"
#define SKEY_GSM_PrimaryModem     "GSM/Primary_Modem"
#define SKEY_GSM_PrimarySmsFormat "GSM/Primary_SMSFormat"
#define SKEY_GSM_PrimaryPIN       "GSM/Primary_PIN"
#define SKEY_GSM_PrimarySCA       "GSM/Primary_SCA"

#define SKEY_GSM_BackupComPort   "GSM/Backup_ComPort"
#define SKEY_GSM_BackupBaudRate  "GSM/Backup_BaudRate"
#define SKEY_GSM_BackupModem     "GSM/Backup_Modem"
#define SKEY_GSM_BackupSmsFormat "GSM/Backup_SMSFormat"
#define SKEY_GSM_BackupPIN       "GSM/Backup_PIN"
#define SKEY_GSM_BackupSCA       "GSM/Backup_SCA"

#define SKEY_GSM_LogMode "GSM/LogMode"
#define SKEY_GSM_LogFile "GSM/LogFile"

// Jabber
#define SKEY_JABBER_PrimaryLoginServer "Jabber/PrimaryLoginServer"
#define SKEY_JABBER_PrimaryUserName    "Jabber/PrimaryUserName"
#define SKEY_JABBER_PrimaryPswd        "Jabber/PrimaryPswd"
#define SKEY_JABBER_PrimarySslMode     "Jabber/PrimarySSLMode"
#define SKEY_JABBER_PrimaryLoginPort   "Jabber/PrimaryLoginPort"

#define SKEY_JABBER_BackupLoginServer  "Jabber/BackupLoginServer"
#define SKEY_JABBER_BackupUserName     "Jabber/BackupUserName"
#define SKEY_JABBER_BackupPswd         "Jabber/BackupPswd"
#define SKEY_JABBER_BackupSslMode      "Jabber/BackupSSLMode"
#define SKEY_JABBER_BackupLoginPort    "Jabber/BackupLoginPort"

// SMS_SMPP1
#define SKEY_SMSSMPP1_Host    "SMS_SMPP1/Host"
#define SKEY_SMSSMPP1_Port    "SMS_SMPP1/Port"
#define SKEY_SMSSMPP1_ID      "SMS_SMPP1/ID"
#define SKEY_SMSSMPP1_Pswd    "SMS_SMPP1/Pswd"
#define SKEY_SMSSMPP1_SrcAddr "SMS_SMPP1/SrcAddr"
#define SKEY_SMSSMPP1_TON     "SMS_SMPP1/TON"
#define SKEY_SMSSMPP1_NPI     "SMS_SMPP1/NPI"

// SMS_SMPP2
#define SKEY_SMSSMPP2_Host    "SMS_SMPP2/Host"
#define SKEY_SMSSMPP2_Port    "SMS_SMPP2/Port"
#define SKEY_SMSSMPP2_ID      "SMS_SMPP2/ID"
#define SKEY_SMSSMPP2_Pswd    "SMS_SMPP2/Pswd"
#define SKEY_SMSSMPP2_SrcAddr "SMS_SMPP2/SrcAddr"
#define SKEY_SMSSMPP2_TON     "SMS_SMPP2/TON"
#define SKEY_SMSSMPP2_NPI     "SMS_SMPP2/NPI"

// RCI
#define SKEY_RCI_Enabled             "RCI/Enabled"
#define SKEY_RCI_Port                "RCI/Port"
#define SKEY_RCI_MaxClients          "RCI/MaxClients"
#define SKEY_RCI_Timeout             "RCI/Timeout"
#define SKEY_RCI_LogAccepted         "RCI/LogAccepted"
#define SKEY_RCI_LogAcceptedWatchDog "RCI/LogAcceptedWatchDog"
#define SKEY_RCI_LogRejected         "RCI/LogRejected"
#define SKEY_RCI_LogRejectedWatchDog "RCI/LogRejectedWatchDog"
#define SKEY_RCI_LogSuccess          "RCI/LogSuccess"
#define SKEY_RCI_LogError            "RCI/LogError"

// Scheduler
#define SKEY_SCHEDULER_Mode1        "Scheduler/Mode1"
#define SKEY_SCHEDULER_Time1        "Scheduler/Time1"
#define SKEY_SCHEDULER_Interval1    "Scheduler/Interval1"
#define SKEY_SCHEDULER_Day1         "Scheduler/Day1"
#define SKEY_SCHEDULER_SchedAlerts1 "Scheduler/SchedAlerts1"

#define SKEY_SCHEDULER_Mode2        "Scheduler/Mode2"
#define SKEY_SCHEDULER_Time2        "Scheduler/Time2"
#define SKEY_SCHEDULER_Interval2    "Scheduler/Interval2"
#define SKEY_SCHEDULER_Day2         "Scheduler/Day2"
#define SKEY_SCHEDULER_SchedAlerts2 "Scheduler/SchedAlerts2"

#define SKEY_SCHEDULER_Mode3        "Scheduler/Mode3"
#define SKEY_SCHEDULER_Time3        "Scheduler/Time3"
#define SKEY_SCHEDULER_Interval3    "Scheduler/Interval3"
#define SKEY_SCHEDULER_Day3         "Scheduler/Day3"
#define SKEY_SCHEDULER_SchedAlerts3 "Scheduler/SchedAlerts3"

#define SKEY_SCHEDULER_Mode4        "Scheduler/Mode4"
#define SKEY_SCHEDULER_Time4        "Scheduler/Time4"
#define SKEY_SCHEDULER_Interval4    "Scheduler/Interval4"
#define SKEY_SCHEDULER_Day4         "Scheduler/Day4"
#define SKEY_SCHEDULER_SchedAlerts4 "Scheduler/SchedAlerts4"

#define SKEY_SCHEDULER_Mode5        "Scheduler/Mode5"
#define SKEY_SCHEDULER_Time5        "Scheduler/Time5"
#define SKEY_SCHEDULER_Interval5    "Scheduler/Interval5"
#define SKEY_SCHEDULER_Day5         "Scheduler/Day5"
#define SKEY_SCHEDULER_SchedAlerts5 "Scheduler/SchedAlerts5"

// TrapListener
#define SKEY_TRAP_Port         "TrapListener/Port"
#define SKEY_TRAP_TrafficCheck "TrapListener/TrafficCheck"
#define SKEY_TRAP_TrafficLimit "TrapListener/TrafficLimit"
#define SKEY_TRAP_TrafficSpan  "TrapListener/TrafficSpan"
#define SKEY_TRAP_Pause        "TrapListener/Pause"
#define SKEY_TRAP_PauseSpan    "TrapListener/PauseSpan"
#define SKEY_TRAP_Action       "TrapListener/Action"
#define SKEY_TRAP_ActionID     "TrapListener/ActionID"

// ActiveRMAServer
#define SKEY_RMA_Enabled     "ActiveRMAServer/Enabled"
#define SKEY_RMA_Port        "ActiveRMAServer/Port"
#define SKEY_RMA_AcceptAnyIP "ActiveRMAServer/AcceptAnyIP"
#define SKEY_RMA_LogAccepted "ActiveRMAServer/LogAccepted"
#define SKEY_RMA_LogRejected "ActiveRMAServer/LogRejected"

#endif // SETTINGS_H
