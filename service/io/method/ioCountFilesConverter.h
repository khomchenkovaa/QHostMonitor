#ifndef IOCOUNTFILESCONVERTER_H
#define IOCOUNTFILESCONVERTER_H

#include "ioTestMethodConverter.h"

#include <QMetaEnum>

//Specific parameters
#define SP_FOLDER     "Folder"
#define SP_MASK       "Mask"
#define SP_SUBFOLDERS "SubFolders"
#define SP_USE_MACROS "UseMacros"
#define SP_COUNTMODE  "CountMode"
#define SP_COUNTVALUE "CountValue"
#define SP_FILESLIMIT "FilesLimit"

namespace SDPO {

class IOCountFilesConverter : public IOTestMethodConverter
{
    Q_OBJECT

    QMetaEnum m_CountConditionEnum;
public:
    explicit IOCountFilesConverter(QObject *parent = 0);

    virtual TestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} //namespace SDPO

#endif // IOCOUNTFILESCONVERTER_H
