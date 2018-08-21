#ifndef TDHCP_H
#define TDHCP_H

#include "tTestMethod.h"

namespace SDPO {

class TDhcp : public TTestMethod
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(QString, RequestIp)

public:
    explicit TDhcp(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TDHCP_H
