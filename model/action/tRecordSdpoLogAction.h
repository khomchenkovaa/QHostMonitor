#ifndef TRECORDSDPOLOGACTION_H
#define TRECORDSDPOLOGACTION_H

#include "tTestAction.h"

namespace SDPO {

class RecordSdpoLogAction : public TestAction
{
    Q_OBJECT

      BOOL_PROPERTY(AddCommonLog) // Add record into common log
      BOOL_PROPERTY(AddPrivateLog) // Add record into private log(if specified for the test)
      BOOL_PROPERTY(AddSpecificLog) // Add record into specific log .txt, .htm or .dbf)
      AUTO_PROPERTY(QString, SpecificLogFile) // Select specific log file
public:
    explicit RecordSdpoLogAction(QObject *parent = nullptr);

      virtual void run(TTest *test);
      virtual QStringList description(bool isBad);
      virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TRECORDSDPOLOGACTION_H
