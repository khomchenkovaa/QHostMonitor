#ifndef PLOGPROPPERTIES_H
#define PLOGPROPPERTIES_H

#include "PropertyHelper.h"

namespace SDPO {

class PLogProperties : public QObject
{
    Q_OBJECT

public: // ENUMS
    enum LogTarget { LT_NONE, LT_FILE, LT_DATABASE };
    Q_ENUMS(LogTaget)

    enum LogMode { LM_FULL, LM_BRIEF, LM_MIDNIGHT, LM_REPLY };
    Q_ENUMS(LogMode)

    enum LogModeTest { LMT_DEFAULT, LMT_BRIEF, LMT_FULL, LMT_REPLY };
    Q_ENUMS(LogModeTest)

    enum LogFormat { LF_HTML, LF_TXT, LF_DBF };
    Q_ENUMS(LogFormat)

    enum LogName { LN_CONST, LN_MONTH, LN_WEEK, LN_DAY };
    Q_ENUMS(LogName)

private:

    AUTO_PROPERTY(LogTarget, Target)
    AUTO_PROPERTY(LogMode, SaveMode)
    AUTO_PROPERTY(LogFormat, Format)
    AUTO_PROPERTY(LogName, NameMethod)
    BOOL_PROPERTY(UseDeadAction)
    AUTO_PROPERTY(int, DeadActionID)
    BOOL_PROPERTY(UseGoodAction)
    AUTO_PROPERTY(int, GoodActionID)
    AUTO_PROPERTY(QString, File2Name)
    AUTO_PROPERTY(QString, OdbcSource)
    AUTO_PROPERTY(QString, OdbcSqlQuery)
    AUTO_PROPERTY(QString, OdbcUser)
    AUTO_PROPERTY(QString, OdbcPassword)
    AUTO_PROPERTY(int, OdbcTimeout)

public:
    explicit PLogProperties(bool primary = true, QObject *parent = nullptr);
    void getPrimaryLogSettings();
    void getBackupLogSettings();
    QString getFileNameByDate(const QDateTime date) const;

    void setSaveModeByTestProps(const LogModeTest lmt);
    void setFormatByFileExt(const QString fileName);

signals:

public slots:

};

} // namespace SDPO

#endif // PLOGPROPPERTIES_H
