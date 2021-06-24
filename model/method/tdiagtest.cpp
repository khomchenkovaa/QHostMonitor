#include "tdiagtest.h"

#include <QProcess>
#include <QRegularExpression>

using namespace SDPO;

/******************************************************************/

TDiagTest::TDiagTest(QObject *parent)
    : TestMethod(TMethodID::Diag, parent)
{
    a_ParamStatus = ParamStatus::INITIAL;
    a_ParamType = 1; // Info
    a_DataType = 2; // Float
    a_Scale = 0;
    a_Timeout = 1;
}

/******************************************************************/

QString TDiagTest::getTestMethod() const
{
    return "Diag Test";
}

/******************************************************************/

QString TDiagTest::getTestedObjectInfo() const
{
    return "Diag: " + getParamDesc();
}

/******************************************************************/

void TDiagTest::run()
{
    writeLogTitle();
    if (fetchData()) {
        statusUpdate();
        m_Result.status = testStatusByParamStatus(a_ParamStatus);
        emit testSuccess();
    } else {
        a_ParamStatus = ParamStatus::UNKNOWN;
        m_Result.status = testStatusByParamStatus(a_ParamStatus);
        emit testFailed();
    }
}

/******************************************************************/

bool TDiagTest::fetchData()
{
    m_Result.clear();

    QString command = getCommand();
    m_Log.append(QString("[Command]$ %1\n\n").arg(command));
    if (command.isEmpty()) {
        m_Result.error = "Command is empty";
        return false;
    }

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        m_Result.error = getTestedObjectInfo() + " can not start";
        m_Result.replyDesc = getTestedObjectInfo() + " can not start";
        process.close();
        return false;
    }
    if(!process.waitForFinished(a_Timeout * 1000)) {
        m_Result.error = getTestedObjectInfo() + " terminated";
        m_Result.replyDesc = getTestedObjectInfo() + " can not start";
        process.close();
        return false;
    }
    if (process.exitCode() != QProcess::NormalExit) {
        m_Result.replyDesc = QString("error %1 in: %2").arg(process.exitCode())
                .arg(command);
        m_Log.append(process.readAll());
        return false;
    }
    QString res = process.readAll();
    m_Log.append(res);
    QStringList resList = res.split("\n");
    if (!resList.isEmpty()) m_Result.reply = resList.takeFirst();
    if (!resList.isEmpty()) m_Result.replyDesc = resList.takeFirst();
    return true;
}

/******************************************************************/
/**
 * Алгоритм определения статуса параметра:
 * 1. Если задано нормальное значение параметра, но не заданы аварийные пределы
 *    значения параметра в процентах от нормального значения, то полученное
 *    значение сравнивается с нормальным, и, по результатам сравнения,
 *    устанавливается соответствующий статус параметра: Normal или Fail.
 *    Пределы значения параметра, заданные в единицах измерения параметра не
 *    анализируются.
 * 2. Если заданы нормальное значение параметра и аварийные пределы значения
 *    параметра в процентах от нормального значения, производится сравнение
 *    полученного значения параметра с заданными пределами, и, по результатам
 *    сравнения, устанавливается соответствующий статус параметра: Normal,
 *    LowWarning, HighWarning, HighFail или LowFail. Пределы значения
 *    параметра, заданные в единицах измерения параметра не анализируются.
 * 3. Если заданы аварийные пределы значения параметра в единицах измерения
 *    параметра, производится сравнение полученного значения параметра с
 *    заданными пределами, и, по результатам сравнения, устанавливается
 *    соответствующий статус параметра: Normal, LowWarning, HighWarning,
 *    HighFail или LowFail.
 * 4. Если не заданы ни нормальное значение параметра, ни аварийные пределы
 *    значения параметра статус параметра устанавливается в Normal.
 */
void TDiagTest::statusUpdate()
{
    ParamStatus status = ParamStatus::NORMAL;
    if (a_DataType == 1) { // data type = string
        status = stringStatus();
    } else { // data type = float
        if (a_NormalValue.isValid()) {
            if (!a_Fail.isValid() && !a_Warning.isValid()) {
                status = floatNormalStatus();
            } else {
                status = floatPercentStatus();
            }
        } else {
            if (a_LowFailLimit.isValid() || a_HighFailLimit.isValid()
                    || a_LowWarningLimit.isValid() || a_HighWarningLimit.isValid()) {
                status = floatLimitStatus();
            }
        }
    }
    if (status != a_ParamStatus) {
        a_ParamStatus = status;
        a_LastChangeDate = QDateTime::currentDateTime().toString();
    }
}

/******************************************************************/

TestMethod *TDiagTest::clone()
{
    TDiagTest *result = new TDiagTest(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_ParamName = a_ParamName;
    result->a_ParamDesc = a_ParamDesc;
    result->a_ParamType = a_ParamType;
    result->a_ParamUnits = a_ParamUnits;
    result->a_DataType = a_DataType;
    result->a_Scale = a_Scale;
    result->a_Subsystem = a_Subsystem;
    result->a_Cmd = a_Cmd;
    result->a_Timeout = a_Timeout;
    result->a_ParamStatus = a_ParamStatus;
    result->a_LastChangeDate = a_LastChangeDate;
    result->a_NormalValue = a_NormalValue;
    result->a_Fail = a_Fail;
    result->a_Warning = a_Warning;
    result->a_LowFailLimit = a_LowFailLimit;
    result->a_LowWarningLimit = a_LowWarningLimit;
    result->a_HighFailLimit = a_HighFailLimit;
    result->a_HighWarningLimit = a_HighWarningLimit;
    return result;
}

/******************************************************************/

ParamStatus TDiagTest::stringStatus()
{
    QRegularExpression re(a_NormalValue.toString());
    if (re.match(m_Result.reply.toString()).hasMatch()) {
        return ParamStatus::NORMAL;
    }
    return ParamStatus::FAIL;
}

/******************************************************************/

ParamStatus TDiagTest::floatNormalStatus()
{
    if (m_Result.reply.toDouble() == a_NormalValue.toDouble()) {
        return ParamStatus::NORMAL;
    }
    return ParamStatus::FAIL;
}

/******************************************************************/

ParamStatus TDiagTest::floatPercentStatus()
{
    double value = m_Result.reply.toDouble();
    double normValue = a_NormalValue.toDouble();
    if (a_Fail.isValid()) {
        double fail = a_Fail.toDouble();
        double lowLimit = normValue * (100 - fail) / 100;
        double highLimit = normValue * (100 + fail) / 100;
        if (value > highLimit) {
            return ParamStatus::HIGH_FAIL;
        } else if (value < lowLimit) {
            return ParamStatus::LOW_FAIL;
        }
    }
    if (a_Warning.isValid()) {
        double warn = a_Warning.toDouble();
        double lowLimit = normValue * (100 - warn) / 100;
        double highLimit = normValue * (100 + warn) / 100;
        if (value > highLimit) {
            return ParamStatus::HIGH_WARNING;
        } else if (value < lowLimit) {
            return ParamStatus::LOW_WARNING;
        }
    }
    return ParamStatus::NORMAL;
}

/******************************************************************/

ParamStatus TDiagTest::floatLimitStatus()
{
    double value = m_Result.reply.toDouble();
    if (a_HighFailLimit.isValid()) {
        if (value > a_HighFailLimit.toDouble()) {
            return ParamStatus::HIGH_FAIL;
        }
    }
    if (a_LowFailLimit.isValid()) {
        if (value < a_LowFailLimit.toDouble()) {
            return ParamStatus::LOW_FAIL;
        }
    }
    if (a_HighWarningLimit.isValid()) {
        if (value > a_HighWarningLimit.toDouble()) {
            return ParamStatus::HIGH_WARNING;
        }
    }
    if (a_LowWarningLimit.isValid()) {
        if (value < a_LowWarningLimit.toDouble()) {
            return ParamStatus::LOW_WARNING;
        }
    }
    return ParamStatus::NORMAL;
}

/******************************************************************/

TestStatus TDiagTest::testStatusByParamStatus(ParamStatus status)
{
    switch (status) {
    case ParamStatus::NORMAL: return TestStatus::Ok;
    case ParamStatus::LOW_WARNING:
    case ParamStatus::HIGH_WARNING: return TestStatus::Warning;
    case ParamStatus::INITIAL: return TestStatus::NotTested;
    case ParamStatus::LOW_FAIL:
    case ParamStatus::HIGH_FAIL:
    case ParamStatus::FAIL: return TestStatus::Bad;
    case ParamStatus::UNKNOWN: break;
    }
    return TestStatus::Unknown;
}

/******************************************************************/
