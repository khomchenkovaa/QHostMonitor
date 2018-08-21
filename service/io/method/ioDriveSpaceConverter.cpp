#include "ioDriveSpaceConverter.h"
#include "gUnit.h"

namespace SDPO {

/***********************************************/

IODriveSpaceConverter::IODriveSpaceConverter(QObject *parent) :
    IOTestMethodConverter(parent)
{
}

/***********************************************/

TTestMethod *IODriveSpaceConverter::getTestMethod()
{
    if (!m_TestMethod) {
        m_TestMethod = new TDriveSpace();
    }
    return m_TestMethod;
}

/***********************************************/

bool IODriveSpaceConverter::setValue(QString key, QString value)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DriveSpace)) {
        return false;
    }
    TDriveSpace *test = qobject_cast<TDriveSpace*>(m_TestMethod);
    if ( key == SP_DRIVE ) {
        test->setDrive(value);
    } else if (key == SP_MIN_FREE_SPACE) {
        GUnit conv(value);
        test->setMinFreeSpace(conv.getValue());
        test->setDimension(conv.getExt());
    } else {
        return false;
    }
    return true;
}

/***********************************************/

void IODriveSpaceConverter::exportTo(QTextStream &out)
{
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DriveSpace)) {
        return;
    }
    TDriveSpace *test = qobject_cast<TDriveSpace*>(m_TestMethod);
    out << SP_DRIVE          << " = " << test->getDrive() << endl;
    out << SP_MIN_FREE_SPACE << " = " << QString::number(test->getMinFreeSpace()) + test->getDimension() << endl;
}

/***********************************************/

} // namespace SDPO
