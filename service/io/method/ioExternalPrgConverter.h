#ifndef IOEXTERNALPRGCONVERTER_H
#define IOEXTERNALPRGCONVERTER_H

#include "ioTestMethodConverter.h"

//Specific parameters
#define SP_COMMANDLINE "CommandLine"
#define SP_ERRORLEVEL  "ErrorLevel"
#define SP_CONDITION   "Condition"
#define SP_KILLAFTER   "KillAfter"
#define SP_WINDOWMODE  "WindowMode"

namespace SDPO {

class IOExternalPrgConverter : public IOTestMethodConverter
{
    Q_OBJECT

    QStringList m_alertMode;
    QStringList m_windowMode;

public:
    explicit IOExternalPrgConverter(QObject *parent = 0);

virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOEXTERNALPRGCONVERTER_H
