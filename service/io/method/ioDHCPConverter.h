#ifndef IODHCPCONVERTER_H
#define IODHCPCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_HOST       "Host"
#define SP_TIMEOUT    "Timeout"
#define SP_REQUEST_IP "RequestIP"

namespace SDPO {

class IODHCPConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IODHCPConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;
};

} //namespace SDPO

#endif // IODHCPCONVERTER_H
