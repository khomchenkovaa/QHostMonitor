#include "miboid.h"

#include <QRegularExpression>

#define MAX_TYPE_NAME_LEN 32
#define STR_BUF_SIZE (MAX_TYPE_NAME_LEN * MAX_OID_LEN)

using namespace SDPO;

/*****************************************************************/

MibOid::MibOid(QVector<oid> *numOID)
{
    oidLen = numOID->size();
    for (size_t i=0; i < oidLen; ++i) {
        oidNum[i] = numOID->at(i);
    }
}

/*****************************************************************/

MibOid::MibOid(oid *numOID, size_t oid_len)
{
    oidLen = oid_len;
    for (size_t i=0; i<oidLen; ++i) {
        oidNum[i] = numOID[i];
    }
}

/*****************************************************************/

void MibOid::addOid(oid item)
{
    oidNum[oidLen] = item;
    oidLen++;
}

/*****************************************************************/

bool MibOid::getNode(const QString &tag)
{
    oidLen = MAX_OID_LEN;
    oidStr = tag;
    int res = get_node(oidStr.toLatin1(), oidNum, &oidLen);
    if (!res) {
        errNo = snmp_errno;
    }
    return res;
}

/*****************************************************************/

bool MibOid::getWildNode(const QString &tag)
{
    oidLen = MAX_OID_LEN;
    oidStr = tag;
    int res = get_wild_node(oidStr.toLatin1(), oidNum, &oidLen);
    if (!res) {
        errNo = snmp_errno;
    }
    return res;
}

/*****************************************************************/

bool MibOid::readObjid(const QString &tag)
{
    oidLen = MAX_OID_LEN;
    oidStr = tag;
    int res = read_objid(oidStr.toLatin1(), oidNum, &oidLen);
    if (!res) {
        errNo = snmp_errno;
    }
    return res;
}

/*****************************************************************/

bool MibOid::concatOidStr(const QString &oidStr)
{
    if (oidStr.isEmpty()) {
        return true; // successfully added nothing
    }
    QStringList strList = oidStr.split('.', QString::SkipEmptyParts);
    if (strList.isEmpty()) {
        return false;
    }
    foreach(const QString& str, strList) {
        addOid(str.toULong());
    }
    return true;
}

/*****************************************************************/

QString MibOid::toString() const
{
    if (hasError()) {
        return oidStr;
    }
    QString result;
    for (size_t i=0; i<oidLen; ++i) {
        result.append(QString(".%1").arg(oidNum[i]));
    }
    return result;
}

/*****************************************************************/

QString MibOid::snprintObjId() const
{
    char str_buf_temp[STR_BUF_SIZE];
    str_buf_temp[0] = '\0';
    snprint_objid(str_buf_temp, sizeof(str_buf_temp), oidNum, oidLen);
    return QString(str_buf_temp);
}

/*****************************************************************/

QString MibOid::errString() const
{
    return snmp_api_errstring(errNo);
}

/*****************************************************************/

MibOid MibOid::parse(const QString &oidStr)
{
    MibOid result;
    result.oidLen = MAX_OID_LEN;
    result.oidStr = oidStr;
    if (!snmp_parse_oid(oidStr.toLatin1(), result.oidNum, &result.oidLen)) {
        result.errNo = snmp_errno;
    }
    return result;
}

/*****************************************************************/

MibOid MibOid::scanNumOid(const QString &numOid)
{
    MibOid result;
    result.oidLen = MAX_OID_LEN;
    result.oidStr = numOid;
    QRegularExpression re("^\\.?(\\d+\\.)*\\d+$");
    QRegularExpressionMatch match = re.match(numOid);
    if (match.hasMatch()) {
        QStringList oidList = numOid.split('.', QString::SkipEmptyParts);
        foreach(const QString oidPart, oidList) {
            result.addOid(oidPart.toULong());
        }
    } else {
        result.oidLen = 0;
    }
    return result;
}

/*****************************************************************/
