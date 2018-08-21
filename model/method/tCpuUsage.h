#ifndef TCPUUSAGE_H
#define TCPUUSAGE_H

#include "tTestMethod.h"

namespace SDPO {

class TCpuUsage : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getComputer())

    AUTO_PROPERTY(QString, Computer)
    AUTO_PROPERTY(QString, OsSelect)
    AUTO_PROPERTY(int, AlertWhen)
    BOOL_PROPERTY(ConnectAs)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)

public:
    explicit TCpuUsage(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TCPUUSAGE_H
