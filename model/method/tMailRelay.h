#ifndef TMAILRELAY_H
#define TMAILRELAY_H

#include "tTestMethod.h"

namespace SDPO {

class TMailRelay : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getOutgoing())
    Q_PROPERTY(QString Path READ  getSender())
    Q_PROPERTY(QString Object READ  getIncoming())

    AUTO_PROPERTY(QString, Outgoing)
    AUTO_PROPERTY(QString, Incoming)
    AUTO_PROPERTY(QString, Sender)

public:
    explicit TMailRelay(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // getters and setters

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

signals:

public slots:

};

} // namespace SDPO

#endif // TMAILRELAY_H
