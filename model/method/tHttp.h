#ifndef THTTP_H
#define THTTP_H

#include "tTestMethod.h"

namespace SDPO {

class THttp : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getHostAddr())
    Q_PROPERTY(QString Path READ getUrl())
    Q_PROPERTY(QString Object READ getUrl())

    AUTO_PROPERTY(QString, Proxy)
    AUTO_PROPERTY(QString, Url)
    AUTO_PROPERTY(QString, Request)
    BOOL_PROPERTY(FollowRedirect)
    AUTO_PROPERTY(int, Timeout)

public:
    explicit THttp(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }

    // getters and setters

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} // namespace SDPO

#endif // THTTP_H
