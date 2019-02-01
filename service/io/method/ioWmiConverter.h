#ifndef IOWMICONVERTER_H
#define IOWMICONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_HOST                  "Host"
#define SP_NAMESPACE             "NameSpace"
#define SP_QUERY                 "Query"
#define SP_ALERTIF               "AlertIf"
#define SP_ALERTIFCOMPARE        "AlertIfCompare"
#define SP_ALERTIFCOUNT          "AlertIfCount"
#define SP_IFINSTALLCHANGED      "IfInstallChanged"

namespace SDPO {

class IOWmiConverter : public IOTestMethodConverter
{
    Q_OBJECT

public:
    explicit IOWmiConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IOWMICONVERTER_H
