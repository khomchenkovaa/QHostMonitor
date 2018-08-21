#ifndef TFILEEXISTS_H
#define TFILEEXISTS_H

#include "tTestMethod.h"

namespace SDPO {

class TFileExists : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString HostAddr READ getHostAddr)
    Q_PROPERTY(QString Path READ getFileName)
    Q_PROPERTY(QString Object READ getObjectProperty)

    AUTO_PROPERTY(QString, FileName)
    BOOL_PROPERTY(TranslateMacros)
    BOOL_PROPERTY(FileExistsCriteria)
    BOOL_PROPERTY(FileOlderFlag)
    BOOL_PROPERTY(FileNewerFlag)
    AUTO_PROPERTY(int, FileOlderValue)
    AUTO_PROPERTY(int, FileNewerValue)

public:
    explicit TFileExists(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }
    QString getObjectProperty() const;

    // getters and setters

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;
};

} // namespace SDPO
#endif // TFILEEXISTS_H
