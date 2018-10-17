#include "tCountFiles.h"

namespace SDPO {

/******************************************************************/

TCountFiles::TCountFiles(QObject *parent) :
    TTestMethod(TMethodID::CountFiles, parent)
{
    a_Folder = QString();
    b_TranslateMacros = false;
    a_FileNameMask = QString("*.*");
    b_IncludeSybFolder = false;
    a_SelectCountFiles = 0; // Count all files
    a_CountValue = 60;
    a_AlertWhen = 100;
}

/******************************************************************/

void TCountFiles::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TCountFiles::clone()
{
    TCountFiles *result = new TCountFiles(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Folder = a_Folder;
    result->b_TranslateMacros = b_TranslateMacros;
    result->a_FileNameMask = a_FileNameMask;
    result->b_IncludeSybFolder = b_IncludeSybFolder;
    result->a_SelectCountFiles = a_SelectCountFiles;
    result->a_CountValue = a_CountValue;
    result->a_AlertWhen = a_AlertWhen;
    return result;
}

/******************************************************************/

QString TCountFiles::getTestMethod() const
{
    return QString("Count Filse: %1\%2").arg(a_Folder).arg(a_FileNameMask);
}

/******************************************************************/

QString TCountFiles::getTestedObjectInfo() const
{
    return QString("Count Files test (%1)").arg(a_Folder);
}

/******************************************************************/


} // namespace SDPO
