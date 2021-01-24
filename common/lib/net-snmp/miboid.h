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
    oid     numOid[MAX_OID_LEN];
    size_t  length = 0;
    QString oidStr;
    int     errNo = 0;

public:
    /*!
     * \brief MibOid default constructor
     */
    explicit MibOid() {}

    /*!
     * \brief MibOid constructor
     * \param oidNum vector of integers that represents the OID numeric notation
     */
    explicit MibOid(QVector<oid> *oidNum);

    /*!
     * \brief MibOid constructor
     * \param oidNum array of integers that represents the OID numeric notation
     * \param oidLen array size
     */
    explicit MibOid(oid *oidNum, size_t oidLen);

    bool isValid() {
        return length > 0;
    }
    bool hasError() const {
        return errNo;
    }
    void addOid(oid item);
    bool getNode(const QString& tag);
    bool getWildNode(const QString& tag);
    bool readObjid(const QString& tag);
    bool concatOidStr(const QString& tag);
    bool isPartOfSubtree(const MibOid& root) const;
    int compare(const MibOid& rOid) const;
    bool equals(const MibOid& rOid) const;
    QString toString() const;
    QString snprintObjId() const;
    QString errString() const;

    static MibOid parse(const QString& objid);
    static MibOid scanNumOid(const QString& objid);
};

} // namespace SDPO

#endif // MIBOID_H
