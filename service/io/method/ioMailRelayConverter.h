#ifndef IOMAILRELAYCONVERTER_H
#define IOMAILRELAYCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_OUTGOING     "File"
#define SP_INCOMING     "UseMacros"
#define SP_SENDER       "OkIfExists"

namespace SDPO {

class IOMailRelayConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOMailRelayConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IOMAILRELAYCONVERTER_H
