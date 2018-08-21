#ifndef IOCOMPAREFILESCONVERTER_H
#define IOCOMPAREFILESCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

static QString SP_ALERTMODE     = QStringLiteral("AlertMode");
static QString SP_MISSINGCHECK  = QStringLiteral("MissingCheck");
static QString SP_USE_MACROS_1  = QStringLiteral("UseMacros1");
static QString SP_USE_MACROS_2  = QStringLiteral("UseMacros2");
static QString SP_FILE_1        = QStringLiteral("File1");
static QString SP_FILE_2        = QStringLiteral("File2");
static QString SP_STRING        = QStringLiteral("String");
static QString SP_ENCODING      = QStringLiteral("Encoding");
static QString SP_CHECKTIME     = QStringLiteral("CheckTime");
static QString SP_CHECKSIZE     = QStringLiteral("CheckSize");
static QString SP_CHECKCONTENT  = QStringLiteral("CheckContent");
static QString SP_WHOLEWORDS    = QStringLiteral("WholeWords");
static QString SP_CASESENSITIVE = QStringLiteral("CaseSensitive");

class IOCompareFilesConverter : public IOTestMethodConverter
{
    Q_OBJECT

    QStringList m_alertMode;
public:
    explicit IOCompareFilesConverter(QObject *parent = 0);

virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOCOMPAREFILESCONVERTER_H
