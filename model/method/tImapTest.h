#ifndef TIMAPTEST_H
#define TIMAPTEST_H

#include "testmethod.h"

namespace SDPO {

class TImapTest : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getServer())
    Q_PROPERTY(QString Object READ getLogin())
    Q_PROPERTY(QString TargetPort READ getPort())


    AUTO_PROPERTY(QString, Server)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Tls)
    AUTO_PROPERTY(QString, Password)
    AUTO_PROPERTY(int, Timeout)
    BOOL_PROPERTY(CheckMailbox)
    AUTO_PROPERTY(QString, MessageFolder)
    AUTO_PROPERTY(QString, MessageStatus)
    AUTO_PROPERTY(QString, MessageAlert)
    AUTO_PROPERTY(int, MessageSize)


public:
    explicit TImapTest(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // getters and setters

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TestMethod *clone() Q_DECL_OVERRIDE;


signals:

public slots:

};

} //namespace SDPO

#endif // TIMAPTEST_H
