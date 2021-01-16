#ifndef SNMPPDU_H
#define SNMPPDU_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include "miboid.h"

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

    bool isValid() {
        return (ptr != nullptr);
    }

    bool noError() {
        if (status == SnmpRespStatSuccess) {
            return (ptr->errstat == SNMP_ERR_NOERROR);
        }
        return false;
    }

    void cleanup() {
        if (ptr) {
            snmp_free_pdu(ptr);
            ptr = nullptr;
        }
        status = SnmpRespStatUnknown;
    }

    void addNullVar(const MibOid& mibOid) {
        snmp_add_null_var(ptr, mibOid.numOid, mibOid.length);
    }

    SnmpPdu fix(SnmpPduType type) {
        return snmp_fix_pdu(ptr, type);
    }

    static SnmpPdu create(SnmpPduType type) {
        return SnmpPdu(snmp_pdu_create(type));
    }

    static SnmpPdu create(SnmpPduType type, const QList<MibOid>& oids) {
        SnmpPdu result = create(type);
        foreach(const MibOid& mibOid, oids) {
            result.addNullVar(mibOid);
        }
        return result;
    }
};

} // namespace SDPO

#endif // SNMPPDU_H
