#ifndef IOFILEEXISTSCONVERTER_H
#define IOFILEEXISTSCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_FILE         "File"
#define SP_USE_MACROS   "UseMacros"
#define SP_OK_IF_EXISTS "OkIfExists"
#define SP_MAX_AGE      "MaxAge"
#define SP_MIN_AGE      "MinAge"

namespace SDPO {

class IOFileExistsConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOFileExistsConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;
    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
};

} // namespace SDPO

#endif // IOFILEEXISTSCONVERTER_H
