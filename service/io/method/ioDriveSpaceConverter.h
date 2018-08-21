#ifndef IODRIVESPACECONVERTER_H
#define IODRIVESPACECONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_DRIVE          = QStringLiteral("Drive");
static QString SP_MIN_FREE_SPACE = QStringLiteral("MinFreeSpace");

class IODriveSpaceConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IODriveSpaceConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;
    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // IODRIVESPACECONVERTER_H
