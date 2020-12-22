#ifndef NETSNMPSESSION_H
#define NETSNMPSESSION_H

#include "snmp.h"

#include <QObject>

#define DEST_HOST_DEFAULT "localhost"
#define COMMUNITY_DEFAULT "public"

namespace SDPO {

class NetSnmpSession : public QObject
{
    Q_OBJECT

    netsnmp_session *m_SessPtr; /**< Net-SNMP session with agent */

public:
    explicit NetSnmpSession(QObject *parent = nullptr);
    ~NetSnmpSession();

    bool open();
    void close();

    SnmpValue get(const QString& oidStr);
    SnmpValue get(const MibOid& anOID);
    QList<SnmpValue> getNext(const QString& oidStr, int cnt = 1);
    QList<SnmpValue> getRow(const QString& oidStr);

    QString errorStr();

    void setDestHost(const QString& host = DEST_HOST_DEFAULT) {
        m_DestHost = host;
    }
    void setCommunity(const QString& community = COMMUNITY_DEFAULT) {
        m_Community = community;
    }
    void setProfile(const SnmpProfile& profile);
    void setTimeout(const int timeout) {
       m_Timeout = timeout;
    }
    void setRetries(const int retries) {
        m_Retries = retries;
    }

    void snmpSessionInit(SnmpSession *session);
    static QString snmpSessionLogError(int priority, const QString& prog, SnmpSession *ss);

private:
    QString     m_DestHost;   /**< default 'localhost', hostname or ip addr of SNMP agent */
    QString     m_Community;  /**< default 'public', SNMP community string (used for both R/W) */
    SnmpVersion m_Version;    /**< default taken from library configuration - probably 3 [1, 2 (same as 2c), 2c, 3] */
    int         m_RemotePort; /**< default '161', allow remote UDP port to be overriden */
    int         m_Timeout;    /**< default '1000000', micro-seconds before retry */
    int         m_Retries;    /**< default '5', retries before failure */
    QString     m_ErrorStr;   /**< read-only, holds the error message assoc. w/ last request */
    int         m_ErrorNum;   /**< read-only, holds the snmp_err or status of last request */
    int         m_ErrorInd;   /**< read-only, holds the snmp_err_index when appropriate */

};

} // namespace SDPO

#endif // NETSNMPSESSION_H
