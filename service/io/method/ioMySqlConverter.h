#ifndef IOMYSQLCONVERTER_H
#define IOMYSQLCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SERVER   "Server"
#define SP_PORT     "Port"
#define SP_DATABASE "Database"
#define SP_USER     "User"
#define SP_PASSWORD "Password"

namespace SDPO {

class IOMySqlConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOMySqlConverter(QObject *parent = 0);

    virtual TestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOMYSQLCONVERTER_H
