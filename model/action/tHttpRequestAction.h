#ifndef THTTPREQUESTACTION_H
#define THTTPREQUESTACTION_H

#include "tTestAction.h"

namespace SDPO {

class HttpRequestAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Host) // Host
    AUTO_PROPERTY(int, Port) // Port
    AUTO_PROPERTY(QString, Request) // Request

public:
    explicit HttpRequestAction(QObject *parent = nullptr);
    virtual ~HttpRequestAction() {}

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();
};

} // namespace SDPO

#endif // THTTPREQUESTACTION_H
