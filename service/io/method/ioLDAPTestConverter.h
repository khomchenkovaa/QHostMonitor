#ifndef IOLDAPTESTCONVERTER_H
#define IOLDAPTESTCONVERTER_H

#include "ioTestMethodConverter.h"

//Specific parameters
#define SP_HOST                 "Host"
#define SP_PORT                 "Port"
#define SP_TIMEOUT              "Timeout"
#define SP_LOGIN                "Login"
#define SP_PASSWORD             "Password"
#define SP_CHECKPERFORMSEARCH   "CheckPerformSearch"
#define SP_BASEOBJECT           "BaseObject"
#define SP_RESLIMIT             "ResLimit"
#define SP_SEARCHFILTER         "SearchFilter"

namespace SDPO {

class IOLDAPTestConverter : public IOTestMethodConverter
{
    Q_OBJECT

public:
    explicit IOLDAPTestConverter(QObject *parent = 0);

    virtual TestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;
};

} //namespace SDPO

#endif // IOLDAPTESTCONVERTER_H
