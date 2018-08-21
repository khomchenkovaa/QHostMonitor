#ifndef TRUNHMSSCRIPTACTION_H
#define TRUNHMSSCRIPTACTION_H

#include "tTestAction.h"

namespace SDPO {

class RunHmsScriptAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, ScriptFile) // Script file

public:
    explicit RunHmsScriptAction(QObject *parent = 0);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TRUNHMSSCRIPTACTION_H
