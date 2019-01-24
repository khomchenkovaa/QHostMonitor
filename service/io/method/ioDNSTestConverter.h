#ifndef IODNSTESTCONVERTER_H
#define IODNSTESTCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SERVER           "Server"
#define SP_TIMEOUT          "Timeout"
#define SP_PROTOCOL         "Protocol"
#define SP_PORT             "Port"
#define SP_REQUEST          "Request"
#define SP_REQUESTYPE       "RequestType"
#define SP_TESTRESULTFOR    "TestResultFor"
#define SP_TESTRESULT       "TestResult"

namespace SDPO {

class IODNSTestConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IODNSTestConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IODNSTESTCONVERTER_H
