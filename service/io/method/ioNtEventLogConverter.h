#ifndef IONTEVENTLOGCONVERTER_H
#define IONTEVENTLOGCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_LOGSOURCE        "LogSource"
#define SP_ALERTCONDITION   "AlertCondition"
#define SP_CONNECTAS        "ConnectAs"
#define SP_COMPABILITY      "Compability"
#define SP_COMPUTERUNC      "ComputerUnc"
#define SP_LOG              "Log"
#define SP_EVENTSOURCE      "EventSource"
#define SP_COMPUTER         "Computer"
#define SP_EVENTTYPE        "EventType"
#define SP_EVENTID          "EventID"
#define SP_DESCRIPTION      "Description"
#define SP_CONNECTTOREMOTE  "ConnectToRemote"
#define SP_LOGIN            "Login"
#define SP_PASSWORD         "Password"

namespace SDPO {

class IONtEventLogConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IONtEventLogConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IONTEVENTLOGCONVERTER_H
