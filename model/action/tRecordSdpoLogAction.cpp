#include "tRecordSdpoLogAction.h"

namespace SDPO {

/******************************************************************/

RecordSdpoLogAction::RecordSdpoLogAction(QObject *parent) :
    TestAction(parent)
{
     setAction(TActionID::LogRecord);
     b_AddCommonLog = false;
     b_AddPrivateLog = false;
     b_AddSpecificLog = false;
}

/******************************************************************/

void RecordSdpoLogAction::run(TTest *test)
{
    Q_UNUSED(test)
    // Action runs from ActionService
}

/******************************************************************/

QStringList RecordSdpoLogAction::description(bool isBad)
{
      QStringList result = TestAction::description(isBad);
      result.append(QString("Use common log: %1").arg(b_AddCommonLog?"Yes":"No"));
      result.append(QString("Use private log: %1").arg(b_AddPrivateLog?"Yes":"No"));
      result.append(QString("Specific log: %1").arg(a_SpecificLogFile));
      return result;
}

/******************************************************************/

TestAction *RecordSdpoLogAction::clone()
{
    RecordSdpoLogAction *result = new RecordSdpoLogAction();
    copyProperties(result);
    result->setAddCommonLog(b_AddCommonLog);
    result->setAddPrivateLog(b_AddPrivateLog);
    result->setAddSpecificLog(b_AddSpecificLog);
    result->setSpecificLogFile(a_SpecificLogFile);
    return result;
}

/******************************************************************/

} // namepsace SDPO
