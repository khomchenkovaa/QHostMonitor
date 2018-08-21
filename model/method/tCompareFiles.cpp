#include "tCompareFiles.h"

namespace SDPO {

/******************************************************************/

TCompareFiles::TCompareFiles(QObject *parent) :
    TTestMethod(TMethodID::FileCompare, parent)
{
//    a_AlertWhen = QString("files are different");
    a_AlertWhen = 0; // files are different
    a_FirstFile = QString();
    a_SecondFile = QString();
    b_TranslateFirstMacros = false;
    b_TranslateSecondMacros = false;
    b_Time = false;
    b_Size = false;
    b_Contents = false;
}

/******************************************************************/

void TCompareFiles::run()
{
    m_Status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TCompareFiles::clone()
{
    TCompareFiles *result = new TCompareFiles(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_AlertWhen = a_AlertWhen;
    result->a_FirstFile = a_FirstFile;
    result->a_SecondFile = a_SecondFile;
    result->b_TranslateFirstMacros = b_TranslateFirstMacros;
    result->b_TranslateSecondMacros = b_TranslateSecondMacros;
    result->a_String = a_String;
    result->a_StringCoding = a_StringCoding;
    result->b_Time = b_Time;
    result->b_Size = b_Size;
    result->b_Contents = b_Contents;
    result->b_CaseSensitive = b_CaseSensitive;
    result->b_WholeWordsOnly = b_WholeWordsOnly;
    return result;
}

/******************************************************************/

QString TCompareFiles::getTestMethod() const
{
    return QString("compare %1 & %2").arg(a_FirstFile).arg(a_SecondFile);
}

/******************************************************************/

QString TCompareFiles::getTestedObjectInfo() const
{
    return QString("file compare (%1 & %2)").arg(a_FirstFile).arg(a_SecondFile);
}

/******************************************************************/

} // namespace SDPO
