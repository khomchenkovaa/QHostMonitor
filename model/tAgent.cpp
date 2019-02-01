#include "tAgent.h"

namespace SDPO {

/***********************************************/

TAgent::TAgent(QObject *parent) :
    QObject(parent)
{
    _name = "HostMonitor";
    _type = HostMonitor;
}

/***********************************************/

TAgent::~TAgent()
{
}

/***********************************************/

} // namespace SDPO
