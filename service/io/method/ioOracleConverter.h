#ifndef IOORACLECONVERTER_H
#define IOORACLECONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SERVER   "Server"
#define SP_USER     "User"
#define SP_PASSWORD "Password"

namespace SDPO {

class IOOracleConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOOracleConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;


};


} // namespace SDPO

#endif // IOORACLECONVERTER_H
