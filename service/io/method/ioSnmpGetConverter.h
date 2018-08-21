#ifndef IOSNMPGETCONVERTER_H
#define IOSNMPGETCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_AGENT     = QStringLiteral("Agent");
static QString SP_COMMUNITY = QStringLiteral("Community");
static QString SP_OID       = QStringLiteral("OID");

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
