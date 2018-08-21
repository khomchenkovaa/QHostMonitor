#ifndef IOCPUUSAGECONVERTER_H
#define IOCPUUSAGECONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_COMPUTER    = QStringLiteral("Computer");
static QString SP_OS          = QStringLiteral("OS");
static QString SP_MAXCPUUSAGE = QStringLiteral("MaxCPUUsage");
static QString SP_USERNAME    = QStringLiteral("Username");

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
