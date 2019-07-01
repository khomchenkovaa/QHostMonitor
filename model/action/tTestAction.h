#ifndef TTESTACTION_H
#define TTESTACTION_H

#include "PropertyHelper.h"
#include "tEnums.h"
#include "tTest.h"
#include "global/tAction.h"

namespace SDPO {

class TestAction : public QObject
{
    Q_OBJECT

    AUTO_PROPERTY(TActionID, Action)
    AUTO_PROPERTY(QString, Name)
    AUTO_PROPERTY(QString, Agent)
    BOOL_PROPERTY(StoreResult)
    AUTO_PROPERTY(TActionMode, Mode)
    AUTO_PROPERTY(int, StartAfter)
    AUTO_PROPERTY(int, Retries)
    AUTO_PROPERTY(QString, Condition)

public:
    explicit TestAction(QObject *parent = nullptr);
    virtual ~TestAction();
//    explicit TestAction(const TestAction &action);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction* clone();
    void copyProperties(TestAction* item);
    bool checkToRun(TTest *test);

signals:
    void actionSuccess();
    void actionFailed();

public slots:

};

} // namespace SDPO

#endif // TTESTACTION_H
