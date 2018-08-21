#include "tActiveScript.h"

namespace SDPO {

/******************************************************************/

TActiveScript::TActiveScript(QObject *parent) :
    TTestMethod(TMethodID::Script, parent)
{
    a_FileScript = QString();
    b_ScriptCriteria = true;
    a_Language = QString("VBScript");
    b_AllowUi = false;
    a_Timeout = 10;
    b_TranslateMacros = false;
}

/******************************************************************/

void TActiveScript::run()
{
    m_Status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

TTestMethod *TActiveScript::clone()
{
    TActiveScript *result = new TActiveScript(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    // test specific
    result->a_FileScript = a_FileScript;
    result->b_ScriptCriteria = b_ScriptCriteria;
    result->a_Language = a_Language;
    result->b_AllowUi = b_AllowUi;
    result->a_Timeout = a_Timeout;
    result->b_TranslateMacros = b_TranslateMacros;
    return result;
}

/******************************************************************/

QString TActiveScript::getTestMethod() const
{
    return QString("Active Script");
}

/******************************************************************/

QString TActiveScript::getTestedObjectInfo() const
{
    if (a_Language == "VBscript")
       return QString("VBscript %1").arg(a_FileScript);
    else
       return QString("Jscript %1").arg(a_FileScript);
}

/******************************************************************/

} // namespace SDPO
