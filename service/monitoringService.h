#ifndef MONITORINGSERVICE_H
#define MONITORINGSERVICE_H

#include <QObject>
#include <QThread>

#include "manageableService.h"
#include "actionService.h"
#include "hmListService.h"

namespace SDPO {

class TTest;
class TNode;

class MonitoringService : public ManageableService
{
    Q_OBJECT

public:
    explicit MonitoringService(HMListService *hml, ActionService *act, int threadCount = QThread::idealThreadCount(), QObject *parent = 0);
    ~MonitoringService();

public slots:
    void clear();
    void runTest(TNode *item);

};

} // namespace SDPO

#endif // MONITORINGSERVICE_H
