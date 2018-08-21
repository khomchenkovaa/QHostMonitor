#ifndef TCOUNTFILES_H
#define TCOUNTFILES_H

#include "tTestMethod.h"

namespace SDPO {

class TCountFiles : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getHostAddr())
    Q_PROPERTY(QString Path READ getFolder())
    Q_PROPERTY(QString Object READ getFolderMask())

    AUTO_PROPERTY(QString, Folder)
    BOOL_PROPERTY(TranslateMacros)
    AUTO_PROPERTY(QString, FileNameMask)
    BOOL_PROPERTY(IncludeSybFolder)
    AUTO_PROPERTY(int, SelectCountFiles)
    AUTO_PROPERTY(int, CountValue)
    AUTO_PROPERTY(int, AlertWhen)

public:
    explicit TCountFiles(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }

    // getters and setters
    QString getFolderMask() const { return QString("%1\%2").arg(a_Folder).arg(a_FileNameMask); }

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;


};

} // namespace SDPO

#endif // TCOUNTFILES_H
