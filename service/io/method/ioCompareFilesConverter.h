#ifndef IOCOMPAREFILESCONVERTER_H
#define IOCOMPAREFILESCONVERTER_H

#include "ioTestMethodConverter.h"

#include <QMetaEnum>

#define SP_ALERTMODE     "AlertMode"
#define SP_MISSINGCHECK  "MissingCheck"
#define SP_USE_MACROS_1  "UseMacros1"
#define SP_USE_MACROS_2  "UseMacros2"
#define SP_FILE_1        "File1"
#define SP_FILE_2        "File2"
#define SP_STRING        "String"
#define SP_ENCODING      "Encoding"
#define SP_CHECKTIME     "CheckTime"
#define SP_CHECKSIZE     "CheckSize"
#define SP_CHECKCONTENT  "CheckContent"
#define SP_WHOLEWORDS    "WholeWords"
#define SP_CASESENSITIVE "CaseSensitive"

namespace SDPO {

class IOCompareFilesConverter : public IOTestMethodConverter
{
    Q_OBJECT

    QMetaEnum m_AlertModeEnum;
public:
    explicit IOCompareFilesConverter(QObject *parent = 0);

    virtual TestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

private:
    QString getCodecNameForMib(int mibEnum);
    int getMibForCodecName(QString name);
};

} //namespace SDPO

#endif // IOCOMPAREFILESCONVERTER_H
