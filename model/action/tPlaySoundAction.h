#ifndef TPLAYSOUNDACTION_H
#define TPLAYSOUNDACTION_H

#include "tTestAction.h"

namespace SDPO {

class PlaySoundAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, File) // Sound file
    BOOL_PROPERTY(WakeUp) // Show WakeUp window and plays sound repeatedly

public:
    explicit PlaySoundAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TPLAYSOUNDACTION_H
