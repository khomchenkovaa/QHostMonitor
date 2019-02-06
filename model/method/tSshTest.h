#ifndef TSSHTEST_H
#define TSSHTEST_H

#include "tTestMethod.h"

namespace SDPO {

class TSshTest : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getSshCmd)

public:
    enum CheckMode {
        cmExitCode,
        cmTextOutput,
        cmScriptResult
    };

    enum ExitCodeMode {
        LT, GT, EQ, NE
    };

    enum TextOutputMode {
        toPresent,
        toAbsent,
        toExpression
    };

private:
    Q_ENUMS(CheckMode)
    Q_ENUMS(ExitCodeMode)
    Q_ENUMS(TextOutputMode)

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(QString, SshCmd)
    AUTO_PROPERTY(CheckMode, Mode)
    AUTO_PROPERTY(ExitCodeMode, ExitCodeCriteria)
    AUTO_PROPERTY(int, ExitCodeValue)
    AUTO_PROPERTY(TextOutputMode, TextOutputCriteria)
    AUTO_PROPERTY(QString, TextOutputValue)
    BOOL_PROPERTY(CaseSensitive)
    BOOL_PROPERTY(WholeWordsOnly)
    BOOL_PROPERTY(TranslateMacros)

public:
    explicit TSshTest(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;
    virtual void parseResult(QString data) Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TSSHTEST_H
