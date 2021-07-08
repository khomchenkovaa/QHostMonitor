#ifndef TDIAGTEST_H
#define TDIAGTEST_H

#include "testmethod.h"

namespace SDPO {

enum class ParamStatus {
    NORMAL = 0,
    LOW_WARNING = 1,
    HIGH_WARNING = 2,
    INITIAL = 3,
    LOW_FAIL = 10,
    HIGH_FAIL = 11,
    FAIL = 13,
    UNKNOWN = 101
};

class TDiagTest : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getCmd())
    Q_PROPERTY(QString Object READ getParamDesc())

    AUTO_PROPERTY(QString, ParamName)
    AUTO_PROPERTY(QString, ParamDesc)
    AUTO_PROPERTY(int, ParamType)
    AUTO_PROPERTY(QString, ParamUnits)
    AUTO_PROPERTY(int, DataType)
    AUTO_PROPERTY(int, Scale)
    AUTO_PROPERTY(QString, Subsystem)
    AUTO_PROPERTY(QString, Cmd)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(ParamStatus, ParamStatus)
    AUTO_PROPERTY(QString, LastChangeDate)
    AUTO_PROPERTY(QVariant, NormalValue)
    AUTO_PROPERTY(QVariant, Fail)
    AUTO_PROPERTY(QVariant, Warning)
    AUTO_PROPERTY(QVariant, LowFailLimit)
    AUTO_PROPERTY(QVariant, LowWarningLimit)
    AUTO_PROPERTY(QVariant, HighFailLimit)
    AUTO_PROPERTY(QVariant, HighWarningLimit)

public:
    explicit TDiagTest(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // getters and setters


    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;

    bool fetchData();
    void statusUpdate();

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

private:
    ParamStatus stringStatus();
    ParamStatus floatNormalStatus();
    ParamStatus floatPercentStatus();
    ParamStatus floatLimitStatus();
    TestStatus testStatusByParamStatus(ParamStatus status);
};

} // namespace SDPO

#endif // TDIAGTEST_H
