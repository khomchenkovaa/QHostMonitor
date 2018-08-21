#ifndef TSHELLSCRIPT_H
#define TSHELLSCRIPT_H

#include "tTestMethod.h"

namespace SDPO {

class TShellScript : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getName)
    Q_PROPERTY(QString Object READ getObjectProperty)
    Q_PROPERTY(QString Object2 READ getObjectProperty2)

    AUTO_PROPERTY(QString, Name)
    AUTO_PROPERTY(QString, Platform)
    AUTO_PROPERTY(QString, StartCmd)
    AUTO_PROPERTY(QString, Script)
    AUTO_PROPERTY(QString, FileName)
    AUTO_PROPERTY(QString, Params)
    AUTO_PROPERTY(int, Timeout)
    BOOL_PROPERTY(TranslateMacros)

public:
    explicit TShellScript(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getObjectProperty() const { return getParam(0); }
    QString getObjectProperty2() const { return getParam(1); }

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;
    virtual void parseResult(QString data) Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

private:
    QString getParam(const int i) const;

};

} // namespace SDPO

#endif // TSHELLSCRIPT_H
