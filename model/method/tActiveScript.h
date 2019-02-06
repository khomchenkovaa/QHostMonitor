#ifndef TACTIVESCRIPT_H
#define TACTIVESCRIPT_H

#include "tTestMethod.h"

namespace SDPO {

class TActiveScript : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getFileScript())
    Q_PROPERTY(QString Object READ getFileScript())
    Q_PROPERTY(QString TestMode READ getLanguage())

    BOOL_PROPERTY(ScriptCriteria)
    AUTO_PROPERTY(QString, FileScript)
    AUTO_PROPERTY(QString, Language)
    BOOL_PROPERTY(AllowUi)
    AUTO_PROPERTY(int, Timeout)
    BOOL_PROPERTY(TranslateMacros)

public:
    explicit TActiveScript(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} // namespace SDPO

#endif // TACTIVESCRIPT_H
