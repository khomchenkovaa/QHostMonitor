#include "startup.h"
#include "qHmlMain.h"

namespace SDPO {

Startup::Startup() :
    QObject(NULL),
    m_mainForm(*new HMLMain(NULL))
{

}

Startup::~Startup()
{
    delete &m_mainForm;
}

void Startup::show() const
{
    m_mainForm.show();
}

} // namespace SDPO


