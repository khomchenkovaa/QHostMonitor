#include "tFileContents.h"
#include <QFileInfo>

namespace SDPO {

/******************************************************************/

TFileContents::TFileContents(QObject *parent) :
    TTestMethod(TMethodID::FileContents, parent)
{
    a_File = QString();
    a_Crc = QString();
    b_RecalculateCrc = false;
}

/******************************************************************/

void TFileContents::run()
{
    m_Result.status = TestStatus::Ok;
    writeLogTitle();
    m_Log.append("File contents method not implemented\n");
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TFileContents::clone()
{
    TFileContents *result = new TFileContents(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_File = a_File;
    result->a_Crc = a_Crc;
    result->b_RecalculateCrc = b_RecalculateCrc;
    return result;

}

/******************************************************************/

QString TFileContents::getTestMethod() const
{
    return QString("%1").arg(a_File);
}

/******************************************************************/

QString TFileContents::getTestedObjectInfo() const
{
    return QString("check file CRC (%1)").arg(a_File);
}

/******************************************************************/

QString TFileContents::getObjectProperty() const
{
    QFileInfo fInfo(a_File);
    return fInfo.baseName();
}

/******************************************************************/

} // namespace SDPO
