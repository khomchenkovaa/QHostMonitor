#ifndef IOPINGCONVERTER_H
#define IOPINGCONVERTER_H

#include "ioTestMethodConverter.h"

// Specific parameters
#define SP_HOST           "Host"
#define SP_TIMEOUT        "Timeout"
#define SP_RETRIES        "Retries"
#define SP_PACKET_SIZE    "PacketSize"
#define SP_DONT_FRAGMENT  "DontFragment"
#define SP_MAX_LOST_RATIO "MaxLostRatio"
#define SP_DISPLAY_MODE   "DisplayMode"

namespace SDPO {

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
