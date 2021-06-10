#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "logProperties.h"
#include "hmListService.h"

#include <QStringList>

namespace SDPO {

class TNode;
class TTest;

class LogService : public QObject
{
    Q_OBJECT

    static QStringList failedLogs;
public:
    explicit LogService(HMListService *hml, QObject *parent = nullptr);
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
    bool writeFileLog(const QString& fileName, const LogProperties &props, TTest *test);
    bool odbcLog(const LogProperties &props, TTest *test);
    bool needToWrite(const LogProperties::LogMode mode, TTest *test) const;
    void reportStatus(const bool logResult, const QString& loggerName, const LogProperties &props, TTest *test);
};

} // namespace SDPO

#endif // LOGSERVICE_H
