#ifndef IODICOMCONVERTER_H
#define IODICOMCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_CALLEDAE  = QStringLiteral("CalledAe");
static QString SP_CALLINGAE = QStringLiteral("CallingAe");


class IODICOMConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IODICOMConverter(QObject *parent = 0);

virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IODICOMCONVERTER_H
