#ifndef IOSHELLSCRIPTCONVERTER_H
#define IOSHELLSCRIPTCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_SCRIPT     = QStringLiteral("Script");
static QString SP_PARAMS     = QStringLiteral("Params");

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
