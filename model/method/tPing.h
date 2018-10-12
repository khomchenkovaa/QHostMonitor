#ifndef TPING_H
#define TPING_H

#include "tTestMethod.h"

namespace SDPO {

class TPing : public TTestMethod
{
    Q_OBJECT

public:
    enum DisplayMode {
        Time, // Reply time - the "Reply" field will represent average reply time
        Lost, // % of lost - display percentage of lost packets
        Received // % of received - display percentage of received packets
    };
    Q_ENUMS(DisplayMode)

private:
    Q_PROPERTY(QString Host READ getAddress)
    Q_PROPERTY(QString HostAddr READ getAddress)

    AUTO_PROPERTY(QString, Address)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(int, PacketSize)
    AUTO_PROPERTY(int, Packets)
    AUTO_PROPERTY(int, TimeToLive)
    BOOL_PROPERTY(DontFragment)
    AUTO_PROPERTY(float, BadCriteria)
    AUTO_PROPERTY(DisplayMode, DisplayMode)

public:
    explicit TPing(QString addr, QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const;
    virtual QString getTestedObjectInfo() const;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;
    virtual void parseResult(QString data) Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

private: // functions
    QString displayModeToString(DisplayMode mode);


};

} // namespace SDPO

#endif // TPING_H
