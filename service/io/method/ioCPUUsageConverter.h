#ifndef IOCPUUSAGECONVERTER_H
#define IOCPUUSAGECONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_COMPUTER    "Computer"
#define SP_OS          "OS"
#define SP_MAXCPUUSAGE "MaxCPUUsage"
#define SP_USERNAME    "Username"
#define SP_PASSWORD    "Password"

namespace SDPO {

class IOCPUUsageConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOCPUUsageConverter(QObject *parent = 0);

virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOCPUUSAGECONVERTER_H
