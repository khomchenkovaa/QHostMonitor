#include "tDicom.h"

namespace SDPO {

/******************************************************************/

TDicom::TDicom(QObject *parent) :
    TTestMethod(TMethodID::DICOM, parent)
{
    a_Host = QString();
    a_Port = 104;
    a_Timeout = 20;
    a_CalledAeTitle = QString("ANY-SCP");
    a_CallingAeTitle = QString("HOSTMON-SCP");
}

/******************************************************************/

void TDicom::run()
{
    m_Result.status = TestStatus::Ok;
    writeLogTitle();
    m_Log.append("DICOM method not implemented\n");
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TDicom::clone()
{
    TDicom *result = new TDicom(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Host = a_Host;
    result->a_Port = a_Port;
    result->a_Timeout = a_Timeout;
    result->a_CalledAeTitle = a_CalledAeTitle;
    result->a_CallingAeTitle = a_CallingAeTitle;
    return result;
}

/******************************************************************/

QString TDicom::getTestMethod() const
{
    return QString("DICOM: %1").arg(a_Host);
}

/******************************************************************/

QString TDicom::getTestedObjectInfo() const
{
    return QString("DICOM test (%1)").arg(a_Host);
}

/******************************************************************/

} // namespace SDPO
