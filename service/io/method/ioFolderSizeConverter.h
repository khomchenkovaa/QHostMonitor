#ifndef IOFOLDERSIZECONVERTER_H
#define IOFOLDERSIZECONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_MAX_SIZE   = QStringLiteral("MaxSize");

class IOFolderSizeConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOFolderSizeConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;
    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IOFOLDERSIZECONVERTER_H
