#include "tWmi.h"

namespace SDPO {

/******************************************************************/

TWmi::TWmi(QObject *parent) :
    TTestMethod(TMethodID::WMI, parent)
{
    a_Host = QString("localhost");
    a_NameSpace = QString("");
    a_Query = QString("");
    a_AlertIf = QString("any HandleCount");
    a_AlertIfCompare = QString("is < than");
    a_AlertIfCount = QString("0");
    a_IfInstanChanged = QString("Unknown status");

}

/******************************************************************/

void TWmi::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TWmi::clone()
{
    TWmi *result = new TWmi(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Host = a_Host;
    result->a_NameSpace = a_NameSpace;
    result->a_Query = a_Query;
    result->a_AlertIf = a_AlertIf;
    result->a_AlertIfCompare = a_AlertIfCompare;
    result->a_AlertIfCount = a_AlertIfCount;
    result->a_IfInstanChanged = a_IfInstanChanged;
    return result;
}

/******************************************************************/

QString TWmi::getTestMethod() const
{
    return QString("WMI HandleCount (%1)").arg(a_Host);
}

/******************************************************************/

QString TWmi::getTestedObjectInfo() const
{
    return QString("WMI: Select HandleCount from (%1)").arg(a_Query);
}

/******************************************************************/

} // namespace SDPO
