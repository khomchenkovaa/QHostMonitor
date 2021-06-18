#ifndef TNAGIOSPLUGIN_H
#define TNAGIOSPLUGIN_H

#include "testmethod.h"

namespace SDPO {

class TNagiosPlugin : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getNagiosPlugin())
    Q_PROPERTY(QString Object READ getNagiosPlugin())

    AUTO_PROPERTY(QString, NagiosPlugin)
    AUTO_PROPERTY(QString, Arguments)
    BOOL_PROPERTY(KillPrg)
    AUTO_PROPERTY(int, KillTimeout)

public:
    explicit TNagiosPlugin(QObject *parent = nullptr);
    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getObjectProperty() const;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

private:
    TestStatus testStatusByExitCode(const int exitCode);
};

} // namespace SDPO

#endif // TNAGIOSPLUGIN_H
