#ifndef ACTIONSERVICE_H
#define ACTIONSERVICE_H

#include <QObject>
#include <QThread>

#include "gData.h"
#include "hmListService.h"

namespace SDPO {

class TNode;
class TTest;
class TestAction;

class ActionService : public QObject
{
    Q_OBJECT

    HMListService *m_HML;
public:
    explicit ActionService(HMListService *hml, QObject *parent = 0);
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
