#include "logService.h"

#include "settings.h"
#include "utils.h"
#include "tTest.h"
#include "logger/textLogger.h"
#include "logger/htmlLogger.h"
#include "logger/dbfLogger.h"
#include "logger/odbcLogger.h"

#include <QDebug>

namespace SDPO {

QStringList LogService::failedLogs;

/***********************************************/

LogService::LogService(HMListService *hml, QObject *parent) :
    QObject(parent)
{
    connect(hml, SIGNAL(testUpdated(TNode*)), SLOT(writeLog(TNode*)));
}

/***********************************************/

LogService::~LogService()
{
    Utils::DestructorMsg(this);
}

/***********************************************/

void LogService::clear()
{
    disconnect(this, SLOT(writeLog(TTest*)));
}

/***********************************************/

void LogService::writeLog(TNode *item)
{
    TTest *test = qobject_cast<TTest*>(item);
    if (test->isUsePrivateLog()) {
        writePrivateLog(test);
    }
    if (test->isUseCommonLog()) {
        writeCommonLog(test);
    }
}

/***********************************************/

void LogService::writePrivateLog(TTest *test)
{
    if (test->getPrivateLog().isEmpty()) {
        return;
    }

    LogProperties logSettings(true);

    // Private log type - files only
    logSettings.setTarget(LogProperties::LT_FILE);
    logSettings.setFormatByFileExt(test->getPrivateLog());
    logSettings.setSaveModeByTestProps(static_cast<LogProperties::LogModeTest>(test->getPrivateLogMode()));
    logSettings.setFile2Name(test->getPrivateLog());
    logSettings.setUseGoodAction(false);
    logSettings.setUseDeadAction(false);

    if (!needToWrite(logSettings.getSaveMode(), test)) {
        return;
    }

    bool logWritten = writeFileLog(logSettings.getFile2Name(), logSettings, test);

    qDebug() << QString("Private (%1):").arg(logWritten)
             << QString("[%1]").arg(test->property("LastTestTime").toString())
             << test->property("HostName").toString()
             << test->property("Status").toString()
             << test->property("Reply").toString()
             << test->property("TestMethod").toString()
             << test->property("TestID").toInt();
}

/***********************************************/

void LogService::writeCommonLog(TTest *test)
{    
    LogProperties logSettings(true);

    logSettings.setSaveModeByTestProps(static_cast<LogProperties::LogModeTest>(test->getCommonLogMode()));
    if (!needToWrite(logSettings.getSaveMode(), test)) {
        return;
    }

    bool logWritten = false;

    switch (logSettings.getTarget()) {
    case LogProperties::LT_NONE :
        logWritten = true;
        break;
    case LogProperties::LT_FILE : {
            QString logFileName = logSettings.getFileNameByDate(test->getTestTime());
            if (!logFileName.isEmpty()) {
                logWritten = writeFileLog(logFileName, logSettings, test);
            }
        }
        break;
    case LogProperties::LT_DATABASE :
        logWritten = odbcLog(logSettings, test);
        break;
    }

    qDebug() << QString("Common (%1):").arg(logWritten)
             << QString("[%1]").arg(test->property("LastTestTime").toString())
             << test->property("HostName").toString()
             << test->property("Status").toString()
             << test->property("Reply").toString()
             << test->property("TestMethod").toString()
             << test->property("TestID").toInt();

    QSettings s;
    bool useBothLogs = s.value(SKEY_LOGGING_UseBothLogs,0) == 1;
    if (!logWritten || useBothLogs) {
        writeBackupLog(test);
    }
}

/***********************************************/

void LogService::writeSpecificFileLog(TTest *test, QString fileName)
{
    if (fileName.isEmpty()) {
        return;
    }

    LogProperties logSettings(true);

    // specific filename log type - files only
    logSettings.setTarget(LogProperties::LT_FILE);
    logSettings.setFormatByFileExt(fileName);
    logSettings.setFile2Name(fileName);
    logSettings.setUseGoodAction(false);
    logSettings.setUseDeadAction(false);

    bool logWritten = writeFileLog(fileName, logSettings, test);

    qDebug() << QString("Specific (%1):").arg(logWritten)
             << QString("[%1]").arg(test->property("LastTestTime").toString())
             << test->property("HostName").toString()
             << test->property("Status").toString()
             << test->property("Reply").toString()
             << test->property("TestMethod").toString()
             << test->property("TestID").toInt();
}

/***********************************************/

void LogService::writeBackupLog(TTest *test)
{
    LogProperties logSettings(false);

    logSettings.setSaveModeByTestProps(static_cast<LogProperties::LogModeTest>(test->getCommonLogMode()));
    if (!needToWrite(logSettings.getSaveMode(), test)) {
        return;
    }

    bool logWritten = false;

    switch (logSettings.getTarget()) {
    case LogProperties::LT_NONE :
        logWritten = true;
        break;
    case LogProperties::LT_FILE : {
            QString logFileName = logSettings.getFileNameByDate(test->getTestTime());
            if (!logFileName.isEmpty()) {
                logWritten = writeFileLog(logFileName, logSettings, test);
            }
        }
        break;
    case LogProperties::LT_DATABASE :
        logWritten = odbcLog(logSettings, test);
        break;
    }

    qDebug() << QString("Backup (%1):").arg(logWritten)
             << QString("[%1]").arg(test->property("LastTestTime").toString())
             << test->property("HostName").toString()
             << test->property("Status").toString()
             << test->property("Reply").toString()
             << test->property("TestMethod").toString()
             << test->property("TestID").toInt();
}

/***********************************************/

bool LogService::writeFileLog(const QString &fileName, const LogProperties &props, TTest *test)
{
    bool logResult = false;

    switch (props.getFormat()) {
    case LogProperties::LF_TXT : {
            TextLogger logger;
            if (logger.startLog(fileName)) {
                logResult = logger.log(test);
                logger.stopLog();
            }
        }
        break;
    case LogProperties::LF_HTML : {
            HtmlLogger logger;
            if (logger.startLog(fileName)) {
                logResult = logger.log(test);
                logger.stopLog();
            }
        }
        break;
    case LogProperties::LF_DBF : {
            DbfLogger logger;
            if (logger.startLog(fileName)) {
                logResult = logger.log(test);
                logger.stopLog();
            }
        }
        break;
    }

    reportStatus(logResult, fileName, props, test );

    return logResult;
}

/***********************************************/

bool LogService::odbcLog( const LogProperties &props, TTest *test)
{
    bool logResult = false;
    OdbcLogger logger;
    if (logger.startLog(props.getOdbcSource(),props.getOdbcUser(),props.getOdbcPassword())) {
        logResult = logger.log(test, props.getOdbcSqlQuery());
        logger.stopLog();
    }

    reportStatus(logResult, props.getOdbcSource(), props, test );

    return logResult;
}

/***********************************************/

bool LogService::needToWrite(const LogProperties::LogMode mode, TTest *test) const
{
    bool result = false;
    switch (mode) {
    case LogProperties::LM_FULL : // save information about every performed test
        result = true;
        break;
    case LogProperties::LM_BRIEF : // write a record when test status changes
        result = (test->status() != test->lastStatus());
        break;
    case LogProperties::LM_MIDNIGHT : { // write a record when test status changes + midnight logging
        QDateTime midnight = test->getTestTime();
        midnight.setTime(QTime(0,0,0,0));
        result = (test->getLastTestTime() < midnight || test->status() != test->lastStatus());
        }
        break;
    case LogProperties::LM_REPLY : // write a record when test status or reply value changes
        result = (test->lastReply() != test->getReply() || test->status() != test->lastStatus());
        break;
    }
    return result;
}

/***********************************************/

void LogService::reportStatus(const bool logResult, const QString &loggerName, const LogProperties &props, TTest *test)
{
    bool wasFailed = failedLogs.contains(loggerName);

    if (logResult && wasFailed) {
        failedLogs.removeAll(loggerName);
        if (props.isUseGoodAction()) {
            emit logAlert(props.getGoodActionID(), test, false);
        }
    }

    if (!logResult && !wasFailed) {
        failedLogs.append(loggerName);
        if (props.isUseDeadAction()) {
            emit logAlert(props.getDeadActionID(), test, true);
        }
    }
}

/***********************************************/

} // namespace SDPO
