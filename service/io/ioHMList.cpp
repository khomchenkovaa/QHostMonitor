#include "ioHMList.h"

#include "utils.h"
#include "hmListService.h"
#include "gData.h"

namespace SDPO {

/******************************************************************/

IOHMList::IOHMList(HMListService *hml, QString fileName, QObject *parent) :
    QObject(parent),
    m_HML(hml),
    m_fileName(fileName)
{
}

/******************************************************************/

IOHMList::~IOHMList()
{
    Utils::DestructorMsg(this);
    if (m_curMethodConverter) {
        delete m_curMethodConverter;
        m_curMethodConverter = 0;
    }
}

/******************************************************************/

} // namespace SDPO
