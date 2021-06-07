#ifndef TFOLDERSIZE_H
#define TFOLDERSIZE_H

#include "testmethod.h"

namespace SDPO {

class TFolderSize : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString HostAddr READ getHostAddr)
    Q_PROPERTY(QString Object READ getObjectProperty)

    AUTO_PROPERTY(QString, Path)
    BOOL_PROPERTY(IncludeSubfolders)
    BOOL_PROPERTY(TranslateMacros)
    AUTO_PROPERTY(qint64, MaxSize)
    AUTO_PROPERTY(QString, Dimension) // b, KB, MB, GB

public:
    explicit TFolderSize(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }
    QString getObjectProperty() const;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

private:
    quint64 diskUsage(const QString &absPath, int &itemCount);
    quint64 diskUsage(const QString &absPath);
};

} // namespace SDPO
#endif // TFOLDERSIZE_H
