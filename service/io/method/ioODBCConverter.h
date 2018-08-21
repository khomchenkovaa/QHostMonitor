#ifndef IOODBCCONVERTER_H
#define IOODBCCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

//Specific parameters
static QString SP_DATASOURCE  = QStringLiteral("Datasource");
static QString SP_LOGIN       = QStringLiteral("Login");
static QString SP_SQLQUERY    = QStringLiteral("SQLQuery");
static QString SP_CHECKFIELD  = QStringLiteral("CheckField");
static QString SP_FIELDROW    = QStringLiteral("FieldRow");
static QString SP_FIELDCOL    = QStringLiteral("FieldCol");
static QString SP_EMPTYSTATUS = QStringLiteral("EmptyStatus");


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
