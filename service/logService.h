#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include <QObject>
#include <QStringList>
#include "options/pLogProperties.h"
#include "hmListService.h"

namespace SDPO {

class TNode;
class TTest;

class LogService : public QObject
{
    Q_OBJECT

    static QStringList failedLogs;
public:
    explicit LogService(HMListService *hml, QObject *parent = 0);
    ~LogService();

signals:
    void logAlert(const int profileId, TTest *test, const bool isBad);

public slots:
    void clear();
    void writeLog(TNode *item);
    void writePrivateLog(TTest *test);
    void writeCommonLog(TTest *test);
    void writeSpecificFileLog(TTest *test, QString fileName);

private:
    void writeBackupLog(TTest *test);
    bool writeFileLog(const QString& fileName, const PLogProperties &props, TTest *test);
    bool odbcLog(const PLogProperties &props, TTest *test);
    bool needToWrite(const PLogProperties::LogMode mode, TTest *test) const;
    void reportStatus(const bool logResult, const QString& loggerName, const PLogProperties &props, TTest *test);
};

} // namespace SDPO

#endif // LOGSERVICE_H
