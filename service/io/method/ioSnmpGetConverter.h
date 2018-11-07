#ifndef IOSNMPGETCONVERTER_H
#define IOSNMPGETCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_AGENT     "Agent"
#define SP_COMMUNITY "Community"
#define SP_TIMEOUT   "Timeout"
#define SP_RETRIES   "Retries"
#define SP_OID       "OID"
#define SP_VALUE     "Value"
#define SP_CONDITION "Condition"

namespace SDPO {

class IOSnmpGetConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOSnmpGetConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;
    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;


};

} // namespace SDPO

#endif // IOSNMPGETCONVERTER_H
