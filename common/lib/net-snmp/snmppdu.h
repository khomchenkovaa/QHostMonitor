#ifndef SNMPPDU_H
#define SNMPPDU_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include "miboid.h"
#include "snmpvar.h"

namespace SDPO {

/*!
 * \brief PDU type to be encapsulated into SNMP message
 */
enum SnmpPduType {
    SnmpPduGet      = SNMP_MSG_GET,      /**< GET request */
    SnmpPduGetNext  = SNMP_MSG_GETNEXT,  /**< GET NEXT request */
    SnmpPduResponse = SNMP_MSG_RESPONSE, /**< Response */
    SnmpPduSet      = SNMP_MSG_SET,      /**< SET request */
    SnmpPduTrap     = SNMP_MSG_TRAP,     /**< Trap message (v1) */
    SnmpPduGetBulk  = SNMP_MSG_GETBULK,  /**< GET BULK request */
    SnmpPduInform   = SNMP_MSG_INFORM,   /**< Inform message */
    SnmpPduTrap2    = SNMP_MSG_TRAP2,    /**< Trap message (v2, v3) */
    SnmpPduReport   = SNMP_MSG_REPORT    /**< Report message */
};

/*!
 * \brief SNMP response status to be used
 */
enum SnmpResponseStatus {
    SnmpRespStatUnknown = -1,           /**< SNMP response not set */
    SnmpRespStatSuccess = STAT_SUCCESS, /**< SNMP response success */
    SnmpRespStatError   = STAT_ERROR,   /**< SNMP response with errors */
    SnmpRespStatTimeout = STAT_TIMEOUT  /**< SNMP response timeout */
};

/*!
 * \brief Net-SNMP request/response PDU wrapper
 * More details in http://www.net-snmp.org/dev/agent/structsnmp__pdu.html
 */
struct SnmpPdu {
    snmp_pdu *ptr = nullptr;
    SnmpResponseStatus status = SnmpRespStatUnknown;

    SnmpPdu(void *pointer = nullptr) {
        this->ptr = static_cast<snmp_pdu*>(pointer);
    }

    bool isValid() const {
        return (ptr != nullptr);
    }

    SnmpPdu clone() const {
        return snmp_clone_pdu(ptr);
    }

    SnmpPdu fix(SnmpPduType type) {
        return snmp_fix_pdu(ptr, type);
    }

    void cleanup() {
        if (ptr) {
            snmp_free_pdu(ptr);
            ptr = nullptr;
        }
        status = SnmpRespStatUnknown;
    }

    SnmpVar addNullVar(const MibOid& mibOid) {
        return snmp_add_null_var(ptr, mibOid.numOid, mibOid.length);
    }

    int addVar(const MibOid& mibOid, char typeChar, const QString value) {
        return snmp_add_var(ptr, mibOid.numOid, mibOid.length, typeChar, value.toLocal8Bit());
    }

    bool noError() const {
        if (status == SnmpRespStatSuccess) {
            return (ptr->errstat == SNMP_ERR_NOERROR);
        }
        return false;
    }

    long errStat() const {
        return ptr->errstat;
    }

    long errIndex() const {
        return ptr->errindex;
    }

    QString errorString() const {
        QString result;
        if (status == SnmpRespStatSuccess) {
            if (ptr->errstat != SNMP_ERR_NOERROR) {
                result = snmp_errstring(static_cast<int>(ptr->errstat));
            }
        }
        return result;
    }

    SnmpVar variables() {
        if (ptr) {
            return ptr->variables;
        }
        return nullptr;
    }

    SnmpVar failedObject() {
        if (ptr->errindex != 0) {
            int count = 1;
            for (SnmpVar var = ptr->variables; var.isValid(); var = var.nextVariable()) {
                if (count == ptr->errindex) {
                    return var;
                }
            }
        }
        return nullptr;
    }

    static SnmpPdu create(SnmpPduType type) {
        return SnmpPdu(snmp_pdu_create(type));
    }

    static SnmpPdu create(SnmpPduType type, const MibOid& anOid) {
        SnmpPdu result = SnmpPdu(snmp_pdu_create(type));
        result.addNullVar(anOid);
        return result;
    }

    static SnmpPdu create(SnmpPduType type, const QList<MibOid>& oids) {
        SnmpPdu result = create(type);
        foreach(const MibOid& anOid, oids) {
            result.addNullVar(anOid);
        }
        return result;
    }
};

} // namespace SDPO

#endif // SNMPPDU_H
