#ifndef IOINTERBASECONVERTER_H
#define IOINTERBASECONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_PROTOCOL = QStringLiteral("Protocol");

class IOInterbaseConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOInterbaseConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOINTERBASECONVERTER_H
