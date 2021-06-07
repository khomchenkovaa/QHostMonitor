#ifndef IOINTERBASECONVERTER_H
#define IOINTERBASECONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SERVER   "Server"
#define SP_DATABASE "Database"
#define SP_USER     "User"
#define SP_PASSWORD "Password"
#define SP_PROTOCOL "Protocol"

namespace SDPO {

class IOInterbaseConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOInterbaseConverter(QObject *parent = 0);

    virtual TestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOINTERBASECONVERTER_H
