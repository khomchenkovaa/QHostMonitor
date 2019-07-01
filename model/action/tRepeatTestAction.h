#ifndef TREPEATTESTACTION_H
#define TREPEATTESTACTION_H

#include "tTestAction.h"

namespace SDPO {

class RepeatTestAction : public TestAction
{
    Q_OBJECT

    BOOL_PROPERTY(RepeatTest) // Repeat test itself
    BOOL_PROPERTY(RecheckTest) // Recheck dependant test items

public:
    explicit RepeatTestAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TREPEATTESTACTION_H
