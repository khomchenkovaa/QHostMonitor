#ifndef TEXECUTEEXTERNALPROGRAMACTION_H
#define TEXECUTEEXTERNALPROGRAMACTION_H

#include "tTestAction.h"

namespace SDPO {

class ExecuteExternalProgramAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, CommandLine) // Command line
    AUTO_PROPERTY(QString, WindowMode) // Window mode

public:
    explicit ExecuteExternalProgramAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TEXECUTEEXTERNALPROGRAMACTION_H
