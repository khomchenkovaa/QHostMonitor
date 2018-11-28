#ifndef IOMSSQLCONVERTER_H
#define IOMSSQLCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SERVER   "Server"
#define SP_DATABASE "Database"
#define SP_LOGIN    "Login"
#define SP_PASSWORD "Password"

namespace SDPO {

class IOMsSqlConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOMsSqlConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOMSSQLCONVERTER_H
