#ifndef IOPOSTGRESQLCONVERTER_H
#define IOPOSTGRESQLCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {


class IOPostgreSqlConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOPostgreSqlConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOPOSTGRESQLCONVERTER_H
