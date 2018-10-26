#ifndef IOSHELLSCRIPTCONVERTER_H
#define IOSHELLSCRIPTCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SCRIPT     "Script"
#define SP_TIMEOUT    "Timeout"
#define SP_USE_MACROS "UseMacros"
#define SP_PARAMS     "Params"

namespace SDPO {

class IOShellScriptConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOShellScriptConverter(QObject *parent = 0);

virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IOSHELLSCRIPTCONVERTER_H
