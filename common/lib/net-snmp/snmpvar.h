#ifndef SNMPVAR_H
#define SNMPVAR_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include "miboid.h"

#include <QVariant>

namespace SDPO {

/*****************************************************************/
/*!
 * \brief SNMP Data type to PDU object
 */
enum SnmpDataType {
    SnmpDataUnknown     = -1,               /**< Unknown type */
    SnmpDataNull        = ASN_NULL,         /**< Null type */
    SnmpDataInteger     = ASN_INTEGER,      /**< Signed Integer type */
    SnmpDataUnsigned    = ASN_UNSIGNED,     /**< Unsigned Integer type */
    SnmpDataOctetString = ASN_OCTET_STR,    /**< Octet String type */
    SnmpDataBits        = ASN_BIT8,         /**< Bits type */
    SnmpDataBitString   = ASN_BIT_STR,      /**< BitString type */
    SnmpDataObjectId    = ASN_OBJECT_ID,    /**< OID type */
    SnmpDataIPAddress   = ASN_IPADDRESS,    /**< IP Address type */
    SnmpDataCounter     = ASN_COUNTER,      /**< Counter type */
    SnmpDataCounter64   = ASN_COUNTER64,    /**< 64 bits Counter type */
    SnmpDataGauge       = ASN_GAUGE,        /**< Gauge type */
    SnmpDataTimeTicks   = ASN_TIMETICKS     /**< Time Ticks type*/
};

/*****************************************************************/
/*!
 * \brief Net-SNMP data value wrapper
 * More details in http://www.net-snmp.org/dev/agent/unionnetsnmp__vardata.html
 */
class SnmpVarData
{
    netsnmp_vardata data;
    SnmpDataType type = SnmpDataUnknown;
    size_t length = 0;

public:
    SnmpVarData(const netsnmp_vardata& varData, const SnmpDataType dataType, const size_t val_lengh) {
        data = varData;
        type = dataType;
        length = val_lengh;
    }

    QVariant value() const;

private:
    QString ipAddress() const;
};

/*****************************************************************/
/*!
 * \brief Net-SNMP variable list wrapper
 * More details in http://www.net-snmp.org/dev/agent/structvariable__list.html
 */
class SnmpVar
{
    netsnmp_variable_list *ptr;

public:
    SnmpVar(void *pointer = nullptr) {
        this->ptr = static_cast<netsnmp_variable_list*>(pointer);
    }

    bool isValid() const {
        return (ptr != nullptr);
    }

    SnmpVar nextVariable() {
        return ptr->next_variable;
    }

    MibOid mibOid() const {
        return MibOid(ptr->name, ptr->name_length);
    }

    SnmpDataType type() const {
        return static_cast<SnmpDataType>(ptr->type);
    }

    QVariant value() const {
        SnmpVarData varData(ptr->val, type(), ptr->val_len);
        return varData.value();
    }

};

/*****************************************************************/

} // namespace SDPO

#endif // SNMPVAR_H
