#ifndef TGENERATEREPORTSACTION_H
#define TGENERATEREPORTSACTION_H

#include "tTestAction.h"

namespace SDPO {
class GenerateReportsAction : public TestAction
{
    Q_OBJECT

    BOOL_PROPERTY(GenerateReportFolder) // Generate Report Folder
    BOOL_PROPERTY(GenerateReportSpecificFolder) // Generate Report Specific Folder
    AUTO_PROPERTY(QString, ReportSelect) // To (recipients)
    AUTO_PROPERTY(QString, RecursiveMode) // To (recipients)
    BOOL_PROPERTY(UseReportPool) // To (recipients)


public:
    explicit GenerateReportsAction(QObject *parent = nullptr);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TGENERATEREPORTSACTION_H
