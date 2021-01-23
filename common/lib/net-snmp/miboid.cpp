#include "miboid.h"

#include <QRegularExpression>

#define MAX_TYPE_NAME_LEN 32
#define STR_BUF_SIZE (MAX_TYPE_NAME_LEN * MAX_OID_LEN)

using namespace SDPO;

/*****************************************************************/

MibOid::MibOid(QVector<oid> *oidNum)
{
    length = oidNum->size();
    for (size_t i=0; i < length; ++i) {
        numOid[i] = oidNum->at(i);
    }
}

/*****************************************************************/

MibOid::MibOid(oid *oidNum, size_t oidLen)
{
    length = oidLen;
    for (size_t i=0; i<length; ++i) {
        numOid[i] = oidNum[i];
    }
}

/*****************************************************************/

void MibOid::addOid(oid item)
{
    numOid[length] = item;
    length++;
}

/*****************************************************************/

bool MibOid::getNode(const QString &tag)
{
    length = MAX_OID_LEN;
    oidStr = tag;
    int res = get_node(oidStr.toLatin1(), numOid, &length);
    if (!res) {
        errNo = snmp_errno;
    }
    return res;
}

/*****************************************************************/

bool MibOid::getWildNode(const QString &tag)
{
    length = MAX_OID_LEN;
    oidStr = tag;
    int res = get_wild_node(oidStr.toLatin1(), numOid, &length);
    if (!res) {
        errNo = snmp_errno;
    }
    return res;
}

/*****************************************************************/

bool MibOid::readObjid(const QString &tag)
{
    length = MAX_OID_LEN;
    oidStr = tag;
    int res = read_objid(oidStr.toLatin1(), numOid, &length);
    if (!res) {
        errNo = snmp_errno;
    }
    return res;
}

/*****************************************************************/

bool MibOid::concatOidStr(const QString &tag)
{
    if (tag.isEmpty()) {
        return true; // successfully added nothing
    }
    QStringList strList = tag.split('.', QString::SkipEmptyParts);
    if (strList.isEmpty()) {
        return false;
    }
    foreach(const QString& str, strList) {
        addOid(str.toULong());
    }
    return true;
}

/*****************************************************************/

bool MibOid::isPartOfSubtree(const MibOid &root) const
{
    if (length < root.length) return false;
    for(size_t i=0; i < root.length; ++i) {
        if (numOid[i] != root.numOid[i]) return false;
    }
    return true;
}

/*****************************************************************/

int MibOid::compare(const MibOid &right) const
{
    return snmp_oid_compare(numOid, length,
                            right.numOid,
                            right.length);
}

/*****************************************************************/

QString MibOid::toString() const
{
    if (hasError()) {
        return oidStr;
    }
    QString result;
    for (size_t i=0; i<length; ++i) {
        result.append(QString(".%1").arg(numOid[i]));
    }
    return result;
}

/*****************************************************************/

QString MibOid::snprintObjId() const
{
    char str_buf_temp[STR_BUF_SIZE];
    str_buf_temp[0] = '\0';
    snprint_objid(str_buf_temp, sizeof(str_buf_temp), numOid, length);
    return QString(str_buf_temp);
}

/*****************************************************************/

QString MibOid::errString() const
{
    return snmp_api_errstring(errNo);
}

/*****************************************************************/

MibOid MibOid::parse(const QString &objid)
{
    MibOid result;
    result.length = MAX_OID_LEN;
    result.oidStr = objid;
    if (!snmp_parse_oid(objid.toLatin1(), result.numOid, &result.length)) {
        result.errNo = snmp_errno;
    }
    return result;
}

/*****************************************************************/

MibOid MibOid::scanNumOid(const QString &objid)
{
    MibOid result;
    result.length = MAX_OID_LEN;
    result.oidStr = objid;
    QRegularExpression re("^\\.?(\\d+\\.)*\\d+$");
    QRegularExpressionMatch match = re.match(objid);
    if (match.hasMatch()) {
        QStringList oidList = objid.split('.', QString::SkipEmptyParts);
        foreach(const QString oidPart, oidList) {
            result.addOid(oidPart.toULong());
        }
    } else {
        result.length = 0;
    }
    return result;
}

/*****************************************************************/
