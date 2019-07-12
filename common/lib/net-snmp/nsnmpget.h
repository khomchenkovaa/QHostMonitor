#ifndef SDPO_SNMPGET_H
#define SDPO_SNMPGET_H

#include "snmp.h"

#include <QObject>

namespace SDPO {

class NSnmpGet : public QObject
{
    Q_OBJECT
public:
    explicit NSnmpGet(QObject *parent = nullptr);
    ~NSnmpGet();

    void setPeername(const QString& host);
    void setVersion(SnmpVersion version);
    void setCommunity(const QString& community);
    void setTimeout(const int timeout);
    void setRetries(const int retries);

    bool request(const QString& oidStr);
    QStringList response() const;
    QString status() const;

signals:

public slots:

private:
    SnmpSession        session, *ss;
    SnmpPdu           *pdu;
    SnmpPdu           *pduResponse;
    SnmpResponseStatus responseStatus;

};

} // namespace SDPO

#endif // SDPO_SNMPGET_H
