#include "tDriveSpace.h"
#include <QStorageInfo>
#include "gUnitConverter.h"

namespace SDPO {

/******************************************************************/

TDriveSpace::TDriveSpace(QObject *parent) :
    TTestMethod(TMethodID::DriveSpace, parent)
{
    m_Drive = QString("/dev/sdb1");
    m_MinFreeSpace = 64;
    m_Dimension = "MB";
}

/******************************************************************/

void TDriveSpace::run()
{
    QString newReply = "No answer";
    float newReplyFloat = 0.0;
    int newReplyInt = 0;
    TestStatus newStatus = TestStatus::Unknown;

    QList<QStorageInfo> drives = QStorageInfo::mountedVolumes();
    foreach(QStorageInfo storage, drives) {
        if (m_Drive != QString(storage.device())) continue;
        float bytesFree = storage.bytesFree();
        float bytesTotal = storage.bytesTotal();
        int testValue = 0;
        if (m_Dimension == "%") {
            testValue = (bytesFree / bytesTotal) * 100.0;
        } else {
            GUnitConverter conv(0,m_Dimension);
            conv.setNumber(bytesFree);
            testValue = conv.fromNumber();
        }

        newReplyInt = testValue;
        newReplyFloat = testValue;
        newReply = QString::number(testValue) + m_Dimension;

        if (testValue < m_MinFreeSpace) {
            newStatus = TestStatus::Bad;
        } else {
            newStatus = TestStatus::Ok;
        }
        break;
    }

    m_Status = newStatus;
    m_Reply = newReply;
    m_ReplyDouble = newReplyFloat;
    m_ReplyInt = newReplyInt;

    emit testSuccess();
}

/******************************************************************/

TTestMethod *TDriveSpace::clone()
{
    TDriveSpace *result = new TDriveSpace(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
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
