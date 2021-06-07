#include "tDriveSpace.h"
#include <QStorageInfo>
#include "gUnitConverter.h"

namespace SDPO {

/******************************************************************/

TDriveSpace::TDriveSpace(QObject *parent) :
    TestMethod(TMethodID::DriveSpace, parent)
{
    m_Drive = QString("/dev/sdb1");
    m_MinFreeSpace = 64;
    m_Dimension = "MB";
}

/******************************************************************/

void TDriveSpace::run()
{
    TTestResult result;
    writeLogTitle();
    QList<QStorageInfo> drives = QStorageInfo::mountedVolumes();
    foreach(QStorageInfo storage, drives) {
        if (m_Drive != QString(storage.device())) continue;
        float bytesFree = storage.bytesFree();
        float bytesTotal = storage.bytesTotal();
        m_Log.append(QString("Drive %1: free=%2, total=%3\n\n").arg(m_Drive).arg(bytesFree).arg(bytesTotal));
        int testValue = 0;
        if (m_Dimension == "%") {
            testValue = (bytesFree / bytesTotal) * 100.0;
        } else {
            GUnitConverter conv(0,m_Dimension);
            conv.setNumber(bytesFree);
            testValue = conv.fromNumber();
        }

        result.replyInt = testValue;
        result.replyDouble = testValue;
        result.reply = QString::number(testValue) + m_Dimension;

        if (testValue < m_MinFreeSpace) {
            result.status = TestStatus::Bad;
        } else {
            result.status = TestStatus::Ok;
        }
        break;
    }

    m_Result = result;

    emit testSuccess();
}

/******************************************************************/

TestMethod *TDriveSpace::clone()
{
    TDriveSpace *result = new TDriveSpace(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->m_Drive = m_Drive;
    result->m_MinFreeSpace = m_MinFreeSpace;
    result->m_Dimension = m_Dimension;
    return result;
}

/******************************************************************/

QString TDriveSpace::getTestMethod() const
{
    return QString("Drive space");
}

/******************************************************************/

QString TDriveSpace::getTestedObjectInfo() const
{
    return QString("Drive space %1").arg(m_Drive);
}

/******************************************************************/

QString TDriveSpace::getDriveObject() const
{
    QFileInfo fInfo(m_Drive);
    return fInfo.baseName();
}

/******************************************************************/

} // namespace SDPO
