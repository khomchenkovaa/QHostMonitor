#ifndef IOPINGCONVERTER_H
#define IOPINGCONVERTER_H

#include "ioTestMethodConverter.h"

namespace SDPO {

// Specific parameters
static QString SP_PACKET_SIZE     = QStringLiteral("PacketSize");
static QString SP_DONT_FRAGMENT   = QStringLiteral("DontFragment");
static QString SP_MAX_LOST_RATIO  = QStringLiteral("MaxLostRatio");
static QString SP_DISPLAY_MODE    = QStringLiteral("DisplayMode");

class IOPingConverter : public IOTestMethodConverter
{
    Q_OBJECT
public:
    explicit IOPingConverter(QObject *parent = 0);

    virtual TTestMethod *getTestMethod() Q_DECL_OVERRIDE;
    virtual bool setValue(QString key, QString value) Q_DECL_OVERRIDE;

    virtual void exportTo(QTextStream &out) Q_DECL_OVERRIDE;

private:
    QString displayModeToString(TPing::DisplayMode mode);

};

} // namespace SDPO

#endif // IOPINGCONVERTER_H
