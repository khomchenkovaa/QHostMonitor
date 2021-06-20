#include "logProperties.h"
#include "settings.h"
#include <QDateTime>

namespace SDPO {

/******************************************************************/

LogProperties::LogProperties(bool primary, QObject *parent) :
    QObject(parent)
{
    if (primary) {
        getPrimaryLogSettings();
    } else {
        getBackupLogSettings();
    }
}

/******************************************************************/

void LogProperties::getPrimaryLogSettings()
{
    QSettings s;
    a_Target        = static_cast<LogTarget>(s.value(SKEY_LOG1_Target, SVAL_LOG1_Target).toInt());
    a_SaveMode      = static_cast<LogMode>  (s.value(SKEY_LOG1_SaveMode, SVAL_LOG1_SaveMode).toInt());
    a_Format        = static_cast<LogFormat>(s.value(SKEY_LOG1_LogFormat, SVAL_LOG1_LogFormat).toInt());
    a_NameMethod    = static_cast<LogName>  (s.value(SKEY_LOG1_LogNameMethod, SVAL_LOG1_LogNameMethod).toInt());
    a_File2Name     = s.value(SKEY_LOG1_File2Name).toString();
    b_UseDeadAction = s.value(SKEY_LOG1_UseDeadAction, SVAL_LOG1_UseDeadAction).toInt();
    a_DeadActionID  = s.value(SKEY_LOG1_DeadActionID, SVAL_LOG1_DeadActionID).toInt();
    b_UseGoodAction = s.value(SKEY_LOG1_UseGoodAction, SVAL_LOG1_UseGoodAction).toInt();
    a_GoodActionID  = s.value(SKEY_LOG1_GoodActionID, SVAL_LOG1_GoodActionID).toInt();
    a_OdbcSource    = s.value(SKEY_LOGGING_OdbcLogSource).toString();
    a_OdbcSqlQuery  = s.value(SKEY_LOGGING_OdbcLogSqlQuery,SVAL_LOGGING_OdbcLogSqlQuery).toString();
    a_OdbcUser      = s.value(SKEY_LOGGING_OdbcLogUser).toString();
    a_OdbcPassword  = s.value(SKEY_LOGGING_OdbcLogPswd).toString();
    a_OdbcTimeout   = s.value(SKEY_LOGGING_OdbcLogTimeout, SVAL_LOGGING_OdbcLogTimeout).toInt();
}

/******************************************************************/

void LogProperties::getBackupLogSettings()
{
    QSettings s;
    a_Target        = static_cast<LogTarget>(s.value(SKEY_LOG2_Target, SVAL_LOG2_Target).toInt());
    a_SaveMode      = static_cast<LogMode>  (s.value(SKEY_LOG2_SaveMode, SVAL_LOG2_SaveMode).toInt());
    a_Format        = static_cast<LogFormat>(s.value(SKEY_LOG2_LogFormat, SVAL_LOG2_LogFormat).toInt());
    a_NameMethod    = static_cast<LogName>  (s.value(SKEY_LOG2_LogNameMethod, SVAL_LOG2_LogNameMethod).toInt());
    a_File2Name     = s.value(SKEY_LOG2_File2Name).toString();
    b_UseDeadAction = s.value(SKEY_LOG2_UseDeadAction, SVAL_LOG2_UseDeadAction).toInt();
    a_DeadActionID  = s.value(SKEY_LOG2_DeadActionID, SVAL_LOG2_DeadActionID).toInt();
    b_UseGoodAction = false;
    a_GoodActionID  = -1; // Do Nothing
    a_OdbcSource    = s.value(SKEY_LOG2_OdbcLogSource).toString();
    a_OdbcSqlQuery  = s.value(SKEY_LOG2_OdbcLogSqlQuery,SVAL_LOGGING_OdbcLogSqlQuery).toString();
    a_OdbcUser      = s.value(SKEY_LOG2_OdbcLogUser).toString();
    a_OdbcPassword  = s.value(SKEY_LOG2_OdbcLogPswd).toString();
    a_OdbcTimeout   = s.value(SKEY_LOG2_OdbcLogTimeout, SVAL_LOG2_OdbcLogTimeout).toInt();
}

/******************************************************************/

QString LogProperties::getFileNameByDate(const QDateTime date) const
{
    QString result = a_File2Name;
    switch (a_NameMethod) {
    case LN_MONTH :
        result.replace("%mmyyyy%",date.toString("MMyyyy"));
        break;
    case LN_WEEK : {
        QString weekNum = QString::number( date.date().weekNumber() );
        if (weekNum.length() < 2) weekNum = "0" + weekNum;
        result.replace("%wwyyyy%",weekNum + date.toString("yyyy"));
        }
        break;
    case LN_DAY :
        result.replace("%ddmmyyyy%",date.toString("ddMMyyyy"));
        break;
    default:
        break;
    }
    return result;
}

/******************************************************************/

void LogProperties::setSaveModeByTestProps(const LogProperties::LogModeTest lmt)
{
    switch (lmt) {
    case LMT_BRIEF : a_SaveMode = LM_BRIEF; break;
    case LMT_FULL : a_SaveMode = LM_FULL; break;
    case LMT_REPLY : a_SaveMode = LM_REPLY; break;
    default: break;
    }
}

/******************************************************************/

void LogProperties::setFormatByFileExt(const QString fileName)
{
    a_Format = LF_TXT;
    if (fileName.endsWith(".htm",Qt::CaseInsensitive)) {
        a_Format = LF_HTML;
    } else if (fileName.endsWith(".dbf",Qt::CaseInsensitive)) {
        a_Format = LF_DBF;
    }
}

/******************************************************************/

} // namespace SDPO
