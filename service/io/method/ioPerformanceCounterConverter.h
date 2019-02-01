#ifndef IOPERFORMANCECOUNTERCONVERTER_H
#define IOPERFORMANCECOUNTERCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_CHECKCOUNTER         "CheckCounter"
#define SP_ALERTWHEN            "AlertWhen"
#define SP_ALERTWHENCOUNTER     "AlertWhenCounter"
#define SP_DISPLAYMODE          "DisplayMode"
#define SP_CONNECTAS            "ConnectAs"
#define SP_LOGIN                "Login"
#define SP_PASSWORD             "Password"

namespace SDPO {

class IOPerformanceCounterConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOPerformanceCounterConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};


} // namespace SDPO

#endif // IOPERFORMANCECOUNTERCONVERTER_H
