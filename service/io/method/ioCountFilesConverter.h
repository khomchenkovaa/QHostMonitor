#ifndef IOCOUNTFILESCONVERTER_H
#define IOCOUNTFILESCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

//Specific parameters
static QString SP_FOLDER        = QStringLiteral("Folder");
static QString SP_MASK          = QStringLiteral("Mask");
static QString SP_COUNTMODE     = QStringLiteral("CountMode");
static QString SP_COUNTVALUE    = QStringLiteral("CountValue");
static QString SP_FILESLIMIT    = QStringLiteral("FilesLimit");

class IOCountFilesConverter : public IOTestMethodConverter
{
    Q_OBJECT

    QStringList m_countMode;

public:
    explicit IOCountFilesConverter(QObject *parent = 0);

virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;

virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOCOUNTFILESCONVERTER_H
