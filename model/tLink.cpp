#include "tLink.h"
#include "tTest.h"

namespace SDPO {

/*************************************************/

TLink::TLink(TTest *test, QObject *parent) :
    TNode(test->getName(), TNode::LINK, parent),
    m_test(test)
{
}

/*************************************************/

QVariant TLink::property(QString name) const
{
    return m_test->property(name);
}

/*************************************************/

QVariant TLink::getGlobal(Macro::Variable globalVar) const
{
    return m_test->getGlobal(globalVar);
}

/*************************************************/

TTest *TLink::getTest() const
{
    return m_test;
}

/*************************************************/

} // namespace SDPO
