#ifndef ODBCLOGGER_H
#define ODBCLOGGER_H

#include <QObject>
#include <QSqlDatabase>

namespace SDPO {

class TTest;

class OdbcLogger : public QObject
{
    Q_OBJECT
    bool m_isStarted;
    QSqlDatabase m_DB;
public:
    explicit OdbcLogger(QObject *parent = 0);
    ~OdbcLogger();

    bool startLog(const QString& dbName, const QString& dbUser, const QString& dbPassword);
    void stopLog();

public slots:
    bool log(TTest* test, QString dbQuery);

};

} // namespace SDPO

#endif // ODBCLOGGER_H
