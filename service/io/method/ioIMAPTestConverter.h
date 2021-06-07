#ifndef IOIMAPTESTCONVERTER_H
#define IOIMAPTESTCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SERVER           "Server"
#define SP_PORT             "Port"
#define SP_LOGIN            "Login"
#define SP_TLS              "Tls"
#define SP_PASSWORD         "Password"
#define SP_TIMEOUT          "Timeout"
#define SP_CHECKMAILBOX     "CheckMailbox"
#define SP_MESSAGEFOLDER    "MessageFolder"
#define SP_MESSAGESTATUS    "MessageStatus"
#define SP_MESSAGEALERT     "MessageAlert"
#define SP_MESSAGESIZE      "MessageSize"

namespace SDPO {

class IOIMAPTestConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOIMAPTestConverter(QObject *parent = 0);

    virtual TestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;
};

} //namespace SDPO

#endif // IOIMAPTESTCONVERTER_H
