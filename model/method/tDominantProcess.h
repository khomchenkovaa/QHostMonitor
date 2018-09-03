#ifndef TDOMINANTPROCESS_H
#define TDOMINANTPROCESS_H

#include "tTestMethod.h"

namespace SDPO {

class TDominantProcess : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getCheckProcessesOn())
    Q_PROPERTY(QString TestMode READ getAlertIf())

    AUTO_PROPERTY(QString, CheckProcessesOn)
    AUTO_PROPERTY(QString, ExcludeProcesses)
    AUTO_PROPERTY(int, AlertIfCount)
    AUTO_PROPERTY(QString, AlertIf)
    AUTO_PROPERTY(QString, TopProcesses)
    BOOL_PROPERTY(ConnectAs)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)

public:
    explicit TDominantProcess(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} //namespace SDPO

#endif // TDOMINANTPROCESS_H
