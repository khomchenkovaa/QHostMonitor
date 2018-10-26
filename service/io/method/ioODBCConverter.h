#ifndef IOODBCCONVERTER_H
#define IOODBCCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_DATASOURCE  "Datasource"
#define SP_LOGIN       "Login"
#define SP_PASSWORD    "Password"
#define SP_TIMEOUT     "Timeout"
#define SP_SQLQUERY    "SQLQuery"
#define SP_CHECKFIELD  "CheckField"
#define SP_FIELDROW    "FieldRow"
#define SP_FIELDCOL    "FieldCol"
#define SP_VALUE       "Value"
#define SP_EMPTYSTATUS "EmptyStatus"

namespace SDPO {

class IOODBCConverter : public IOTestMethodConverter
{
    Q_OBJECT

    QStringList m_criteriaMode;
public:
    explicit IOODBCConverter(QObject *parent = 0);

virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOODBCCONVERTER_H
