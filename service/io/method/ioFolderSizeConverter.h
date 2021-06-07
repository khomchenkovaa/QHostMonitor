#ifndef IOFOLDERSIZECONVERTER_H
#define IOFOLDERSIZECONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_FILE       "File"
#define SP_SUBFOLDERS "SubFolders"
#define SP_USE_MACROS "UseMacros"
#define SP_MAX_SIZE   "MaxSize"
#define SP_DIMENSION  "Dimension"

namespace SDPO {

class IOFolderSizeConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOFolderSizeConverter(QObject *parent = 0);

    virtual TestMethod *getTestMethod() Q_DECL_OVERRIDE;

    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;
    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;
    virtual QJsonObject toJsonObject() Q_DECL_OVERRIDE;
    virtual TestMethod *fromJsonObject(QJsonObject jsonObj) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IOFOLDERSIZECONVERTER_H
