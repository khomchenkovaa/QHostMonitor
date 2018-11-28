#ifndef IOFILECONTENTSCONVERTER_H
#define IOFILECONTENTSCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_FILE             "File"
#define SP_CRC              "Crc"
#define SP_RECALCULATECRC   "RecalculateCrc"

namespace SDPO {

class IOFileContentsConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOFileContentsConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;
};

} //namespace SDPO

#endif // IOFILECONTENTSCONVERTER_H
