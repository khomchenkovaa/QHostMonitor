#ifndef TORACLE_H
#define TORACLE_H

#include "testmethod.h"

namespace SDPO {

class TOracle : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Object READ getDatabase())

    AUTO_PROPERTY(QString, Database)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, Password)

public:
    explicit TOracle(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TORACLE_H
