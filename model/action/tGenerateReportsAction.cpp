#include "tGenerateReportsAction.h"

namespace SDPO {

/******************************************************************/

GenerateReportsAction::GenerateReportsAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::Report);
}

/******************************************************************/

void GenerateReportsAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Do nothing
}

/******************************************************************/

QStringList GenerateReportsAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
        if (b_GenerateReportFolder)
            result.append(QString("Use contains folder"));
        else if (b_GenerateReportSpecificFolder)
            result.append(QString("Folder:%1").arg(a_ReportSelect));
        result.append(QString("Recursion:%1").arg(a_RecursiveMode));
    return result;
}

/******************************************************************/

TestAction *GenerateReportsAction::clone()
{
    GenerateReportsAction *result = new GenerateReportsAction();
    copyProperties(result);
    result->setGenerateReportFolder(b_GenerateReportFolder);
    result->setGenerateReportSpecificFolder(b_GenerateReportSpecificFolder);
    result->setReportSelect(a_ReportSelect);
    result->setRecursiveMode(a_RecursiveMode);
    result->setUseReportPool(b_UseReportPool);
    return result;
}

/******************************************************************/

} //namespace SDPO
