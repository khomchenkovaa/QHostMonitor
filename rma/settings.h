#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#define ORGANIZATION_NAME   "SNIIP"
#define ORGANIZATION_DOMAIN "www.sniip.ru"
#define APPLICATION_NAME    "RMA"
#define APPLICATION_VERSION "1.0 for Linux"

#define RMA_PATH     "Basic/RmaPath"
#define RMA_TMP_DIR  "Basic/TmpDir"
#define RMA_COMMENT  "Basic/Comment"

// Connection
#define RMA_HOST     "Basic/Host"
#define RMA_PORT     "Basic/Port"
#define RMA_TIMEOUT  "Basic/Timeout"
#define RMA_PASSWORD "Basic/Password"

// Logging
#define LOG_SUCCESS      "Logging/LogSuccess"
#define LOG_OK_FILE      "Logging/OkLogFile"
#define LOG_FAILS        "Logging/LogFails"
#define LOG_BAD_FILE     "Logging/BadLogFile"
#define LOG_VERBOSE_FILE "Logging/VerboseLogFile"

// Security
#define FLT_ACTIVE   "IncomeFilter/FilterActive"
#define FLT_LIST     "IncomeFilter/FilterList"
#define FLT_MARKS    "IncomeFilter/FilterMarks"
#define RM_UPD_ALLOW "RemoteManagment/AllowUpdates"
#define RM_UPD_ADDR  "RemoteManagment/UpdateAddr"
#define RM_MNG_ALLOW "RemoteManagment/AllowManage"
#define RM_MNG_ADDR  "RemoteManagment/ManageAddr"

// Enabled Tests
#define TEST_PING          "EnabledTests/Ping"
#define TEST_TCP           "EnabledTests/TCP"
#define TEST_UDP           "EnabledTests/UDP"
#define TEST_UNC           "EnabledTests/UNC"
#define TEST_FOLDER_SIZE   "EnabledTests/FolderSize"
#define TEST_COUNT_FILES   "EnabledTests/CountFiles"
#define TEST_FILE_EXISTS   "EnabledTests/FileExists"
#define TEST_TEXT_LOG      "EnabledTests/TextLog"
#define TEST_FILE_CRC      "EnabledTests/FileCRC"
#define TEST_COMPARE_FILES "EnabledTests/CompareFiles"
#define TEST_PROCESS       "EnabledTests/Process"
#define TEST_CPU_USAGE     "EnabledTests/CPUUsage"
#define TEST_SCRIPT        "EnabledTests/Script"
#define TEST_EXTERNAL      "EnabledTests/External"
#define TEST_ODBC          "EnabledTests/ODBC"
#define TEST_SNMP          "EnabledTests/SNMP"
#define TEST_SHELL_SCRIPT  "EnabledTests/ShellScript"

// Enabled Actions
#define ACT_EXECUTE "EnabledActions/ExecuteAction"
#define ACT_TCP_UDP "EnabledActions/TcpUdpAction"
#define ACT_SYSLOG  "EnabledActions/SyslogAction"

// Tests
#define SCRIPT_CPU_USAGE "Tests/CPUUsageScript"
#define SCRIPT_PROC_CNT  "Tests/ProcCntScript"
#define SCRIPT_PROC_LIST "Tests/ProcListScript"

/*
    // RMA Settings
    AUTO_PROPERTY(QString, RmaPath)
    AUTO_PROPERTY(QString, TmpDir)
    AUTO_PROPERTY(QString, Comment)
    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(QString, Password)

    // Logging settings
    BOOL_PROPERTY(LogSuccess)
    AUTO_PROPERTY(QString, OkLogFile)
    BOOL_PROPERTY(LogFails)
    AUTO_PROPERTY(QString, BadLogFile)
    AUTO_PROPERTY(QString, VerboseLogFile)

    // Security settings
    BOOL_PROPERTY(FilterActive)
    AUTO_PROPERTY(QString, FilterList)
    AUTO_PROPERTY(QString, FilterMask)
    BOOL_PROPERTY(AllowManage)
    AUTO_PROPERTY(QString, ManageAddr)
    BOOL_PROPERTY(AllowUpdate)
    AUTO_PROPERTY(QString, UpdateAddr)

    // Test settings
    AUTO_PROPERTY(QString, CPUUsageScript)
    AUTO_PROPERTY(QString, ProcCntScript)
    AUTO_PROPERTY(QString, ProcListScript)
 */

#endif // SETTINGS_H
