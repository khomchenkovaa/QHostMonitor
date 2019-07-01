#ifndef TCHANGETESTINTERVALACTION_H
#define TCHANGETESTINTERVALACTION_H

#include "tTestAction.h"
#include <QTime>

namespace SDPO {

class ChangeTestIntervalAction : public TestAction
{
    Q_OBJECT

    BOOL_PROPERTY(RestoreValue) // Restore origin value
    BOOL_PROPERTY(SetToTime) // Set to (HH:MM:SS)
    BOOL_PROPERTY(SetToPercent) // Set to % of the current value
    AUTO_PROPERTY(QTime, TimeValueSelect) // Time
    AUTO_PROPERTY(int, Percent) // Percent

public:
    explicit ChangeTestIntervalAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TCHANGETESTINTERVALACTION_H
