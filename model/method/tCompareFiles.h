#ifndef TCOMPAREFILES_H
#define TCOMPAREFILES_H

#include "tTestMethod.h"

namespace SDPO {

class TCompareFiles : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getFirstFile())
    Q_PROPERTY(QString Object READ getFirstFile())
    Q_PROPERTY(QString Object2 READ getSecondFile())
    Q_PROPERTY(QString TestMode READ getAlertWhen())

    AUTO_PROPERTY(int, AlertWhen)
    AUTO_PROPERTY(QString, FirstFile)
    AUTO_PROPERTY(QString, SecondFile)
    BOOL_PROPERTY(TranslateFirstMacros)
    BOOL_PROPERTY(TranslateSecondMacros)
    AUTO_PROPERTY(QString, String)
    AUTO_PROPERTY(QString, StringCoding)
    BOOL_PROPERTY(Time)
    BOOL_PROPERTY(Size)
    BOOL_PROPERTY(Contents)
    BOOL_PROPERTY(CaseSensitive)
    BOOL_PROPERTY(WholeWordsOnly)

public:
    explicit TCompareFiles(QObject *parent = 0);

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

#endif // TCOMPAREFILES_H
