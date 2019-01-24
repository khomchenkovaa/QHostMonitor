#ifndef IONTPTESTCONVERTER_H
#define IONTPTESTCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SERVER       "Server"
#define SP_PORT         "Port"
#define SP_RETRIES      "Retries"
#define SP_TIMEOUT      "Timeout"
#define SP_ALERTWHEN    "AlertWhen"
#define SP_SEC          "Sec"
#define SP_DISPLAYMODE  "DisplayMode"

namespace SDPO {

class IONtpTestConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IONtpTestConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} // namespace SDPO


#endif // IONTPTESTCONVERTER_H
