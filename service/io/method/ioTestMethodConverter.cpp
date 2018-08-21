#include "ioTestMethodConverter.h"

namespace SDPO {

/***********************************************/

IOTestMethodConverter::IOTestMethodConverter(QObject *parent) :
    QObject(parent)
{
    m_TestMethod = 0;
}

/***********************************************/

bool IOTestMethodConverter::setValue(QString key, QString value)
{
    Q_UNUSED(key)
    Q_UNUSED(value)
    return false;
}

/***********************************************/

void IOTestMethodConverter::exportTo(QTextStream &out)
{
    Q_UNUSED(out)
}

/***********************************************/

} // namespace SDPO
