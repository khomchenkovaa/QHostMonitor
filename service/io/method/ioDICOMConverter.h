#ifndef IODICOMCONVERTER_H
#define IODICOMCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_HOST      "Host"
#define SP_PORT      "Port"
#define SP_TIMEOUT   "Timeout"
#define SP_CALLEDAE  "CalledAe"
#define SP_CALLINGAE "CallingAe"

namespace SDPO {

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
