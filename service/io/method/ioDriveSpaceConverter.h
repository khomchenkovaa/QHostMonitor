#ifndef IODRIVESPACECONVERTER_H
#define IODRIVESPACECONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_DRIVE          "Drive"
#define SP_MIN_FREE_SPACE "MinFreeSpace"

namespace SDPO {

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
