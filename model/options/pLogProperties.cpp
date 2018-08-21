#include "pLogProperties.h"
#include "mSettings.h"
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
    a_Target = (LogTarget) Settings::get(Settings::Logging1, Settings::Target, QVariant(1)).toInt();
    a_SaveMode = (LogMode) Settings::get(Settings::Logging1, Settings::SaveMode, QVariant(2)).toInt();
    a_Format = (LogFormat) Settings::get(Settings::Logging1, Settings::LogFormat, QVariant(0)).toInt();
    a_NameMethod = (LogName) Settings::get(Settings::Logging1, Settings::LogNameMethod, QVariant(0)).toInt();
    a_File2Name = Settings::get(Settings::Logging1, Settings::File2Name, QVariant()).toString();
    b_UseDeadAction = Settings::get(Settings::Logging1, Settings::UseDeadAction, QVariant(0)).toInt() == 1;
    a_DeadActionID = Settings::get(Settings::Logging1, Settings::DeadActionID, QVariant(-1)).toInt();
    b_UseGoodAction = Settings::get(Settings::Logging1, Settings::UseGoodAction, QVariant(0)).toInt() == 1;
    a_GoodActionID = Settings::get(Settings::Logging1, Settings::GoodActionID, QVariant(-1)).toInt();
    a_OdbcSource = Settings::get(Settings::Logging, Settings::odbcLogSource, QVariant()).toString();
    a_OdbcSqlQuery = Settings::get(Settings::Logging, Settings::odbcLogSQLQuer, QVariant("Insert into hmlog (eventtime, testname, status, reply, testid, testmethod) VALUES ('%DateTime%', '%TestName%', '%Status%', '%Reply%', %TestID%, '%TestMethod%')")).toString();
    a_OdbcUser = Settings::get(Settings::Logging, Settings::odbcLogUser, QVariant()).toString();
    a_OdbcPassword = Settings::get(Settings::Logging, Settings::odbcLogPswd, QVariant()).toString();
    a_OdbcTimeout = Settings::get(Settings::Logging, Settings::odbcLogTimeout, QVariant(10)).toInt();
}

/******************************************************************/

void PLogProperties::getBackupLogSettings()
{
    a_Target = (LogTarget) Settings::get(Settings::Logging2, Settings::Target, QVariant(1)).toInt();
    a_SaveMode = (LogMode) Settings::get(Settings::Logging2, Settings::SaveMode, QVariant(2)).toInt();
    a_Format = (LogFormat) Settings::get(Settings::Logging2, Settings::LogFormat, QVariant(0)).toInt();
    a_NameMethod = (LogName) Settings::get(Settings::Logging2, Settings::LogNameMethod, QVariant(0)).toInt();
    a_File2Name = Settings::get(Settings::Logging2, Settings::File2Name, QVariant()).toString();
    b_UseDeadAction = Settings::get(Settings::Logging2, Settings::UseDeadAction, QVariant(0)).toInt() == 1;
    a_DeadActionID = Settings::get(Settings::Logging2, Settings::DeadActionID, QVariant(-1)).toInt();
    b_UseGoodAction = false;
    a_GoodActionID = -1; // Do Nothing
    a_OdbcSource = Settings::get(Settings::Logging2, Settings::odbcLogSource, QVariant()).toString();
    a_OdbcSqlQuery = Settings::get(Settings::Logging2, Settings::odbcLogSQLQuer, QVariant("Insert into hmlog (eventtime, testname, status, reply, testid, testmethod) VALUES ('%DateTime%', '%TestName%', '%Status%', '%Reply%', %TestID%, '%TestMethod%')")).toString();
    a_OdbcUser = Settings::get(Settings::Logging2, Settings::odbcLogUser, QVariant()).toString();
    a_OdbcPassword = Settings::get(Settings::Logging2, Settings::odbcLogPswd, QVariant()).toString();
    a_OdbcTimeout = Settings::get(Settings::Logging2, Settings::odbcLogTimeout, QVariant(10)).toInt();
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
