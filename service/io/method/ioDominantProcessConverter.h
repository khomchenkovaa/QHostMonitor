#ifndef IODOMINANTPROCESSCONVERTER_H
#define IODOMINANTPROCESSCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_CHECKPROCESSON       "CheckProcessOn"
#define SP_EXCLUDEPROCESSES     "ExcludeProcesses"
#define SP_ALERTIFCOUNT         "AlertIfCount"
#define SP_ALERTIF              "AlertIf"
#define SP_TOPPROCESSES         "TopProcesses"
#define SP_LOGIN                "Login"
#define SP_PASSWORD             "Password"

namespace SDPO {

class IODominantProcessConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IODominantProcessConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IODOMINANTPROCESSCONVERTER_H
