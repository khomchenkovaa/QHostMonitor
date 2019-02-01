#include "pLogProperties.h"
#include "gSettings.h"
#include <QDateTime>

namespace SDPO {

/******************************************************************/

PLogProperties::PLogProperties(bool primary, QObject *parent) :
    QObject(parent)
{
    if (primary) {
        getPrimaryLogSettings();
    } else {
        getBackupLogSettings();
    }
}

/******************************************************************/

void PLogProperties::getPrimaryLogSettings()
{
    QSettings s;
    a_Target = (LogTarget) s.value(SKEY_LOG1_Target,1).toInt();
    a_SaveMode = (LogMode) s.value(SKEY_LOG1_SaveMode,2).toInt();
    a_Format = (LogFormat) s.value(SKEY_LOG1_LogFormat,0).toInt();
    a_NameMethod = (LogName) s.value(SKEY_LOG1_LogNameMethod,0).toInt();
    a_File2Name = s.value(SKEY_LOG1_File2Name).toString();
    b_UseDeadAction = s.value(SKEY_LOG1_UseDeadAction,0).toInt() == 1;
    a_DeadActionID = s.value(SKEY_LOG1_DeadActionID,-1).toInt();
    b_UseGoodAction = s.value(SKEY_LOG1_UseGoodAction,0).toInt() == 1;
    a_GoodActionID = s.value(SKEY_LOG1_GoodActionID,-1).toInt();
    a_OdbcSource = s.value(SKEY_LOGGING_OdbcLogSource).toString();
    a_OdbcSqlQuery = s.value(SKEY_LOGGING_OdbcLogSqlQuery,SVAL_LOGGING_OdbcQuery).toString();
    a_OdbcUser = s.value(SKEY_LOGGING_OdbcLogUser).toString();
    a_OdbcPassword = s.value(SKEY_LOGGING_OdbcLogPswd).toString();
    a_OdbcTimeout = s.value(SKEY_LOGGING_OdbcLogTimeout).toInt();
}

/******************************************************************/

void PLogProperties::getBackupLogSettings()
{
    QSettings s;
    a_Target = (LogTarget) s.value(SKEY_LOG2_Target,1).toInt();
    a_SaveMode = (LogMode) s.value(SKEY_LOG2_SaveMode,2).toInt();
    a_Format = (LogFormat) s.value(SKEY_LOG2_LogFormat,0).toInt();
    a_NameMethod = (LogName) s.value(SKEY_LOG2_LogNameMethod,0).toInt();
    a_File2Name = s.value(SKEY_LOG2_File2Name).toString();
    b_UseDeadAction = s.value(SKEY_LOG2_UseDeadAction,0).toInt() == 1;
    a_DeadActionID = s.value(SKEY_LOG2_DeadActionID,-1).toInt();
    b_UseGoodAction = false;
    a_GoodActionID = -1; // Do Nothing
    a_OdbcSource = s.value(SKEY_LOG2_OdbcLogSource).toString();
    a_OdbcSqlQuery = s.value(SKEY_LOG2_OdbcLogSqlQuery,SVAL_LOGGING_OdbcQuery).toString();
    a_OdbcUser = s.value(SKEY_LOG2_OdbcLogUser).toString();
    a_OdbcPassword = s.value(SKEY_LOG2_OdbcLogPswd).toString();
    a_OdbcTimeout = s.value(SKEY_LOG2_OdbcLogTimeout).toInt();
}

/******************************************************************/

QString PLogProperties::getFileNameByDate(const QDateTime date) const
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

void PLogProperties::setSaveModeByTestProps(const PLogProperties::LogModeTest lmt)
{
    switch (lmt) {
    case LMT_BRIEF : a_SaveMode = LM_BRIEF; break;
    case LMT_FULL : a_SaveMode = LM_FULL; break;
    case LMT_REPLY : a_SaveMode = LM_REPLY; break;
    default: break;
    }
}

/******************************************************************/

void PLogProperties::setFormatByFileExt(const QString fileName)
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
