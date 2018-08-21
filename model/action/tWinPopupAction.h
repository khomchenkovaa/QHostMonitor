#ifndef TWINPOPUPACTION_H
#define TWINPOPUPACTION_H

#include "tTestAction.h"

namespace SDPO {

class WinPopupAction : public TestAction
{
    Q_OBJECT
public:
    explicit WinPopupAction(QObject *parent = 0);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TWINPOPUPACTION_H
