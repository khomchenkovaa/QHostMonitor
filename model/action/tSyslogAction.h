#ifndef TSYSLOGACTION_H
#define TSYSLOGACTION_H

#include "tTestAction.h"

namespace SDPO {

class SyslogAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Server) // Server
    AUTO_PROPERTY(int, Port) // Port
    AUTO_PROPERTY(QString, Message) // Message
    AUTO_PROPERTY(QString, Severity) // Severity
    AUTO_PROPERTY(int, Facility) // Facility

public:
    explicit SyslogAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSYSLOGACTION_H
