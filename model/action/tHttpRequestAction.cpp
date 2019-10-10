#include "tHttpRequestAction.h"

namespace SDPO {

/******************************************************************/

HttpRequestAction::HttpRequestAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::HttpRequest);
}

/******************************************************************/

void HttpRequestAction::run(TTest *test)
{
    Q_UNUSED(test)
    // TODO HttpRequestAction::run implementation
}

/******************************************************************/

QStringList HttpRequestAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("%1").arg(a_Request));
    return result;
}

/******************************************************************/

TestAction *HttpRequestAction::clone()
{
    HttpRequestAction *result = new HttpRequestAction();
    copyProperties(result);
    result->setHost(a_Host);
    result->setPort(a_Port);
    result->setRequest(a_Request);
    return result;
}

/******************************************************************/

} // namespace SDPO
