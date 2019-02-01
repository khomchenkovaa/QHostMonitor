#ifndef TSNMPGET_H
#define TSNMPGET_H

#include "tTestMethod.h"

namespace SDPO {

class TSnmpGet : public TTestMethod
{
    Q_OBJECT

public:
    enum Condition {
        LessThan,MoreThan,EqualTo,DifferentFrom,
        Contain,NotContain,
        IncreaseBy,DecreaseBy,ChangeBy,
        IncByPercent,DecByPercent,ChangeByPercent,
        IncSec,DecSec,ChangeSec
    };
    Q_ENUMS(Condition)

private:

    Q_PROPERTY(QString HostAddr READ getHost)
    Q_PROPERTY(QString MibNameShort READ getMibName)

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(QString, Community)
    AUTO_PROPERTY(QString, MibOid)
    AUTO_PROPERTY(QString, MibName)
    AUTO_PROPERTY(QString, OidFullName)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(int, Retries)
    AUTO_PROPERTY(QString, Value)
    AUTO_PROPERTY(QString, Version)

    Condition a_Condition;

public:    
    explicit TSnmpGet(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // getters and setters
    Condition getCondition() const { return a_Condition; }
    void setCondition(const Condition value) { a_Condition = value; }

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;
    virtual void parseResult(QString data) Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

    // helpers
    QString conditionToString(Condition cond) const;
    Condition conditionFromString(QString condStr, Condition condDefault) const;
};

} // namespace SDPO

#endif // TSNMPGET_H
