#ifndef IOEXTERNALPRGCONVERTER_H
#define IOEXTERNALPRGCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

//Specific parameters
static QString SP_COMMANDLINE = QStringLiteral("CommandLine");
static QString SP_ERRORLEVEL  = QStringLiteral("ErrorLevel");
static QString SP_KILLAFTER   = QStringLiteral("KillAfter");
static QString SP_WINDOWMODE  = QStringLiteral("WindowMode");

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
