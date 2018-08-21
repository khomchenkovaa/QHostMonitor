#ifndef IOFILEEXISTSCONVERTER_H
#define IOFILEEXISTSCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_OK_IF_EXISTS = QStringLiteral("OkIfExists");
static QString SP_MAX_AGE      = QStringLiteral("MaxAge");
static QString SP_MIN_AGE      = QStringLiteral("MinAge");

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
