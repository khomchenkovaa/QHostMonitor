#ifndef NETSNMPSESSION_H
#define NETSNMPSESSION_H

#include "snmp.h"
#include "snmppdu.h"
#include "snmpprofile.h"

#include <QObject>

#define DEST_HOST_DEFAULT "localhost"
#define COMMUNITY_DEFAULT "public"

#define NET_SNMP_SESSION_DESTHOST   "DestHost"
#define NET_SNMP_SESSION_COMMUNITY  "Community"
#define NET_SNMP_SESSION_VERSION    "Version"
#define NET_SNMP_SESSION_TIMEOUT    "Timeout"
#define NET_SNMP_SESSION_RETRIES    "Retries"
#define NET_SNMP_SESSION_LOCALPORT  "LocalPort"

#define NET_SNMP_CMD_OIDS           "oids"

namespace SDPO {

struct SnmpTableColumn {
    oid     subid;
    QString label;
    QString fmt;
};


/*!
 * \brief Net-SNMP session with agent wrapper
 * More details in http://www.net-snmp.org/dev/agent/structsnmp__session.html
 */
class NetSnmpSession : public QObject
{
    Q_OBJECT

    netsnmp_session *m_SessPtr; /**< Net-SNMP session with agent */
    QString m_AddrString;

public:
    explicit NetSnmpSession(QObject *parent = nullptr);
    ~NetSnmpSession();

    bool open();
    void close();
    netsnmp_session *ss() {
        return m_SessPtr;
    }

    SnmpPdu synchResponse(const SnmpPdu& request);

    SnmpValue get(const QString& oidStr);
    SnmpValueList get(const QList<MibOid>& oids);
    SnmpValueList get(const QStringList& oids);
    SnmpValueList get(const QVariantMap& map);
    SnmpValueList getNext(const QList<MibOid>& oids);
    SnmpValueList getRow(const QString& oidStr);
    SnmpValue set(const QString& oidStr, const QVariant& oidValue);
    SnmpValueList bulkGet(const QList<MibOid>& names, int nonRepeaters = 0, int maxRepetitions = 10);
    SnmpValueList bulkWalk(const MibOid& rootOid, int nonRepeaters = 0, int maxRepetitions = 10,
                              bool checkLexicographic = false, bool includeRequested = true);

    QString addrString() const {
        return m_AddrString;
    }
    QString errorStr();
    SnmpValue errorValue(const MibOid& anOid, const SnmpPdu& pdu);
    void setProfile(const SnmpProfile& profile);

    /*! snmp version */
    void setVersion(SnmpVersion version) {
        if (m_Version != version) {
            m_Reopen = true;
            m_Version = version;
        }
    }
    /*! Number of retries before timeout */
    void setRetries(const int retries) {
        if (m_Retries != retries) {
            m_Reopen = true;
            m_Retries = retries;
        }
    }
    /*! Number of uS until first timeout, then exponential backoff */
    void setTimeout(const long timeout) {
        if (m_Timeout != timeout) {
            m_Reopen = true;
            m_Timeout = timeout;
        }
    }
    /*! Number of sec until first timeout, then exponential backoff */
    void setTimeoutSec(const long timeout) {
        setTimeout(timeout * 1000000L);
    }
    /*! name or address of default peer (may include transport specifier and/or port number) */
    void setDestHost(const QString& host = DEST_HOST_DEFAULT) {
        if (m_DestHost != host) {
            m_Reopen = true;
            m_DestHost = host;
        }
    }
    QString destHost() const {
        return m_DestHost;
    }
    /*! community for outgoing requests (SNMPv1 & SNMPv2c field) */
    void setCommunity(const QString& community) {
        if (m_Community != community) {
            m_Reopen = true;
            m_Community = community;
        }
    }

signals:
    void error(const QString& msg);

public:
    QList<MibNode> readColumns(const QString &oidStr);
    SnmpValueTable getTableRows(const QList<MibOid> &columns);

private:
    bool        m_Reopen = false;
    bool        m_FixPdu = true; // FIXME no setter
    QString     m_DestHost;     /**< default 'localhost', hostname or ip addr of SNMP agent */
    QString     m_Community;    /**< default 'public', SNMP community string (used for both R/W) */
    SnmpVersion m_Version;      /**< default taken from library configuration - probably 3 [1, 2 (same as 2c), 2c, 3] */
    long        m_Timeout;      /**< default '1000000', micro-seconds before retry */
    int         m_Retries;      /**< default '1', retries before failure */
    QString     m_ErrorStr;     /**< read-only, holds the error message assoc. w/ last request */
    int         m_ErrorNum = 0; /**< read-only, holds the snmp_err or status of last request */
    int         m_ErrorInd = 0; /**< read-only, holds the snmp_err_index when appropriate */

};

} // namespace SDPO

#endif // NETSNMPSESSION_H
