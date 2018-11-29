#ifndef IOACTIVESCRIPTCONVERTER_H
#define IOACTIVESCRIPTCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_SCRIPTCRITERIA       "ScriptCriteria"
#define SP_FILESCRIPT           "FileScript"
#define SP_LANGUAGE             "Language"
#define SP_ALLOWUI              "AllowUi"
#define SP_TIMEOUT              "Timeout"
#define SP_TRANSLATEMACROS      "TranslateMacros"

namespace SDPO {

class IOActiveScriptConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOActiveScriptConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TTestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;
};

} //namespace SDPO

#endif // IOACTIVESCRIPTCONVERTER_H
