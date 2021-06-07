#include "tSshTest.h"

namespace SDPO {

/******************************************************************/

TSshTest::TSshTest(QObject *parent) :
    TestMethod(TMethodID::SSH, parent)
{
    a_Port = 20;
    a_Timeout = 5000;
    a_Mode = CheckMode::cmExitCode;
    a_ExitCodeCriteria = ExitCodeMode::LT;
    a_ExitCodeValue = 0;
    a_TextOutputCriteria = TextOutputMode::toPresent;
    b_CaseSensitive = false;
    b_WholeWordsOnly = false;
    b_TranslateMacros = false;
}

/******************************************************************/

QString TSshTest::getTestMethod() const
{
    return "SSH test";
}

/******************************************************************/

QString TSshTest::getTestedObjectInfo() const
{
    return QString();
}

/******************************************************************/

void TSshTest::run()
{
    m_Result.status = TestStatus::Ok;
    emit testSuccess();
}

/******************************************************************/

QString TSshTest::getCommand() const
{
    return QString();
}

/******************************************************************/

void TSshTest::parseResult(QString data)
{
    Q_UNUSED(data)
}

/******************************************************************/

TestMethod *TSshTest::clone()
{
    TSshTest *result = new TSshTest(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Host = a_Host;
    result->a_Port = a_Port;
    result->a_Timeout = a_Timeout;
    result->a_SshCmd = a_SshCmd;
    result->a_Mode = a_Mode;
    result->a_ExitCodeCriteria = a_ExitCodeCriteria;
    result->a_ExitCodeValue = a_ExitCodeValue;
    result->a_TextOutputCriteria = a_TextOutputCriteria;
    result->a_TextOutputValue = a_TextOutputValue;
    result->b_CaseSensitive = b_CaseSensitive;
    result->b_WholeWordsOnly = b_WholeWordsOnly;
    result->b_TranslateMacros = b_TranslateMacros;
    return result;
}

/******************************************************************/

} // namespace SDPO
