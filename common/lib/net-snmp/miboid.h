#ifndef MIBOID_H
#define MIBOID_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <QString>
#include <QVector>

namespace SDPO {

/*!
 * @brief MibOid class that wraps Net-SNMP oid array
 */
class MibOid
{
public:
    oid    oidNum[MAX_OID_LEN];
    size_t oidLen = 0;
    QString oidStr;
    int    errNo = 0;

public:
    /*!
     * \brief MibOid default constructor
     */
    explicit MibOid() {}

    /*!
     * \brief MibOid constructor
     * \param numOID vector of integers that represents the OID numeric notation
     */
    explicit MibOid(QVector<oid> *numOID);

    /*!
     * \brief MibOid constructor
     * \param numOID array of integers that represents the OID numeric notation
     * \param oid_len array length
     */
    explicit MibOid(oid *numOID, size_t oid_len);

    bool isValid() {
        return oidLen > 0;
    }
    bool hasError() const {
        return errNo;
    }
    void addOid(oid item);
    bool getNode(const QString& tag);
    bool getWildNode(const QString& tag);
    bool readObjid(const QString& tag);
    bool concatOidStr(const QString& oidStr);
    QString toString() const;
    QString snprintObjId() const;
    QString errString() const;

    static MibOid parse(const QString& oidStr);
    static MibOid scanNumOid(const QString& numOid);
};

} // namespace SDPO

#endif // MIBOID_H
