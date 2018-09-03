#ifndef TFILECONTENTS_H
#define TFILECONTENTS_H

#include "tTestMethod.h"

namespace SDPO {

class TFileContents : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ getHostAddr())
    Q_PROPERTY(QString Path READ getFile())
    Q_PROPERTY(QString Object READ getObjectProperty())

    AUTO_PROPERTY(QString, File)
    AUTO_PROPERTY(QString, Crc)
    BOOL_PROPERTY(RecalculateCrc)

public:
    explicit TFileContents(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }
    QString getObjectProperty() const;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} // namespace SDPO

#endif // TFILECONTENTS_H
