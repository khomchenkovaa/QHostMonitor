#include "ioDriveSpaceConverter.h"
#include "gUnitConverter.h"

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
        GUnitConverter conv(value);
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

QJsonObject IODriveSpaceConverter::toJsonObject()
{
    QJsonObject jsonObj;
    if (!m_TestMethod || (m_TestMethod->getTMethodID() != TMethodID::DriveSpace)) {
        return jsonObj;
    }
    TDriveSpace* test = qobject_cast<TDriveSpace*>(m_TestMethod);
    jsonObj.insert(SP_DRIVE, QJsonValue(test->getDrive()));
    jsonObj.insert(SP_MIN_FREE_SPACE, QJsonValue(QString::number(test->getMinFreeSpace()) + test->getDimension()));
    return jsonObj;
}

/***********************************************/

TTestMethod *IODriveSpaceConverter::fromJsonObject(QJsonObject jsonObj)
{
    TDriveSpace *test = qobject_cast<TDriveSpace*>(getTestMethod());
    test->setDrive(jsonObj.value(SP_DRIVE).toString());
    GUnitConverter conv(jsonObj.value(SP_MIN_FREE_SPACE).toString());
    test->setMinFreeSpace(conv.getValue());
    test->setDimension(conv.getExt());
    return test;
}

/***********************************************/

} // namespace SDPO
