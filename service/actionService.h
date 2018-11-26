#ifndef ACTIONSERVICE_H
#define ACTIONSERVICE_H

#include <QObject>
#include <QThread>

#include "manageableService.h"
#include "gData.h"
#include "hmListService.h"
#include "logService.h"

namespace SDPO {

class TNode;
class TTest;
class TestAction;

class ActionService : public ManageableService
{
    Q_OBJECT

    HMListService *m_HML;
    LogService    *m_Log;
public:
    explicit ActionService(HMListService *hml, LogService *log, QObject *parent = 0);
    ~ActionService();

signals:
    void actionWinPopup(TTest *test);
    void actionWriteCommonLog(TTest *test);
    void actionWritePrivateLog(TTest *test);
    void actionWriteSpecificFileLog(TTest *test, QString fileName);

public slots:
    void clear();
    void runActions(TNode *item);
    void runProfile(const int profileId, TTest *test, const bool isBad);

private:
    void tryToRun(TTest *test, TestAction *action);
};

} // namespace SDPO

#endif // ACTIONSERVICE_H
