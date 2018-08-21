#ifndef MONITORINGSERVICE_H
#define MONITORINGSERVICE_H

#include <QObject>
#include <QThread>

#include "PropertyHelper.h"

namespace SDPO {

class TTest;
class TNode;

class MonitoringService : public QObject
{
    Q_OBJECT

    BOOL_PROPERTY(Paused)

public:
    explicit MonitoringService(int threadCount = QThread::idealThreadCount(), QObject *parent = 0);
    ~MonitoringService();

public slots:
    void clear();
    void runTest(TNode *item);

};

} // namespace SDPO

#endif // MONITORINGSERVICE_H
