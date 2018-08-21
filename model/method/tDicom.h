#ifndef TDICOM_H
#define TDICOM_H

#include "tTestMethod.h"

#define DICOM_DEFAULT_PORT 104

namespace SDPO {

class TDicom : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString TargetPort READ getPort)

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(QString, CalledAeTitle)
    AUTO_PROPERTY(QString, CallingAeTitle)

public:
    explicit TDicom(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TDICOM_H
