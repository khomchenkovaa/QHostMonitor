#ifndef IOHTTPCONVERTER_H
#define IOHTTPCONVERTER_H

#include "ioTestMethodConverter.h"

//Specific parameters
#define SP_PROXY            "Proxy"
#define SP_URL              "Url"
#define SP_REQUEST          "Request"
#define SP_FOLLOWREDIRECT   "FollowRedirect"
#define SP_TIMEOUT          "Timeout"

namespace SDPO {

class IOHTTPConverter : public IOTestMethodConverter
{
    Q_OBJECT

public:
    explicit IOHTTPConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;
};

} //namespace SDPO

#endif // IOHTTPCONVERTER_H
