#ifndef DBFLOGGER_H
#define DBFLOGGER_H

#include <QObject>
#include "qdbf/qdbftablemodel.h"

namespace SDPO {

class TTest;

class DbfLogger : public QObject
{
    Q_OBJECT
    bool m_isStarted;
    QDbf::QDbfTableModel m_model;
public:
    explicit DbfLogger(QObject *parent = 0);
    ~DbfLogger();

    bool startLog(const QString &logFileName);
    void stopLog();

public slots:
    bool log(TTest* test);
private:
    bool createLogFile(const QString &logFileName);
};

} // namespace SDPO

#endif // DBFLOGGER_H
