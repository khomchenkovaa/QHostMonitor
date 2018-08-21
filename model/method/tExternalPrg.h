#ifndef TEXTERNALPRG_H
#define TEXTERNALPRG_H

#include "tTestMethod.h"

namespace SDPO {

class TExternalPrg : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getExternalPrg())
    Q_PROPERTY(QString Object READ getExternalPrg())

    AUTO_PROPERTY(QString, ExternalPrg)
    AUTO_PROPERTY(int, AlertMode)
    AUTO_PROPERTY(int, ExitCode)
    AUTO_PROPERTY(int, WinMode)
    BOOL_PROPERTY(KillPrg)
    AUTO_PROPERTY(int, KillTimeout)

public:
    explicit TExternalPrg(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getObjectProperty() const;

    // getters and setters


    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE { return getExternalPrg(); }

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

private:
    TestStatus testStatusByExitCode(const int exitCode);

};

} // namespace SDPO

#endif // TEXTERNALPRG_H
