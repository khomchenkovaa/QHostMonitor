#include "oidstring.h"

#include <QRegularExpression>
#include <QDebug>

#define MAX_TYPE_NAME_LEN 32
#define STR_BUF_SIZE (MAX_TYPE_NAME_LEN * MAX_OID_LEN)

using namespace SDPO;

/**********************************************************************/

OidString::OidString(const QString& str)
    : oidStr(str)
{

}

/**********************************************************************/

bool OidString::isEmpty() const
{
    return oidStr.isEmpty();
}

/**********************************************************************/

bool OidString::isNumeric() const
{
    QRegularExpression re("^\\.?(\\d+\\.)*\\d+$");
    QRegularExpressionMatch match = re.match(oidStr);
    return match.hasMatch();
}

/**********************************************************************/

QString OidString::translateToOid(bool autoInit, int bestGuess)
{
    if (autoInit) {
        netsnmp_init_mib(); /* vestigial */
    }

    /* Save old output format and set to FULL so long_names works */
    int oldFormat = netsnmp_ds_get_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_OID_OUTPUT_FORMAT); // Current NETSNMP_DS_LIB_OID_OUTPUT_FORMAT
    netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_OID_OUTPUT_FORMAT, NETSNMP_OID_OUTPUT_FULL);

    QString result;
    MibOid mibOid;

    if (!tag2oid(QString(), mibOid, NULL, bestGuess)) {
        if (NetSNMP::verbose) qWarning() << "error:snmp_translate_obj:Unknown OID " << oidStr;
    } else {
        result = mibOid.toString();
    }

    netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_OID_OUTPUT_FORMAT, oldFormat);
    return result;
}

/**********************************************************************/

QString OidString::translateToTag(bool useLong, bool autoInit, bool includeModuleName)
{
    if (autoInit) {
        netsnmp_init_mib(); /* vestigial */
    }

    /* Save old output format and set to FULL so long_names works */
    int oldFormat = netsnmp_ds_get_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_OID_OUTPUT_FORMAT); // Current NETSNMP_DS_LIB_OID_OUTPUT_FORMAT
    netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_OID_OUTPUT_FORMAT, NETSNMP_OID_OUTPUT_FULL);

    MibOid mibOid;
    mibOid.concatOidStr(oidStr);
    QString result = mibOid.snprintObjId();
    if (!useLong) {
        QString label;
        QString iid;
        bool status = getLabelIid(result, label, iid, NoFlags);
        if (status && !label.isEmpty()) {
            result = label;
            if (!iid.isEmpty()) {
                result.append('.');
                result.append(iid);
            }
        }
    }
    /* Prepend modulename:: if enabled */
    if (includeModuleName) {
        QString modName;
        MibNode moduleTree = MibNode::findByOid(mibOid);
        if (moduleTree.isValid()) {
            modName = moduleTree.moduleName();
            if (modName == "#-1") {
                modName = "UNKNOWN::";
            } else {
                modName.append("::");
            }
        }
        result.prepend(modName);
    }

    netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_OID_OUTPUT_FORMAT, oldFormat);
    return result;
}

/**********************************************************************/

MibNode OidString::tag2oid(const QString &iid, MibOid &mibOid, int *type, int bestGuess)
{
    // SRC static struct tree * __tag2oid _((char *, char *, oid  *, size_t *, int *, int));
    MibNode result;
    if (oidStr.isEmpty()) {
        return result;
    }
    /*********************************************************
     * bestGuess = 0 - same as no switches (read_objid) if multiple parts,
     *                 or uses find_node if a single leaf
     * bestGuess = 1 - same as -Ib (get_wild_node)
     * bestGuess = 2 - same as -IR (get_node)
     *********************************************************/
    if (bestGuess == 1 || bestGuess == 2) {
        MibOid newOid = MibOid::scanNumOid(oidStr); // make sure it's not a numeric tag
        if (!newOid.isValid()) {
            if (bestGuess == 2) { // Random search -IR
                if (newOid.getNode(oidStr)) {
                    result = MibNode::findByOid(newOid);
                }
            } else if (bestGuess == 1) { // Regex search -Ib
                MibNode::clearTreeFlags();
                if (newOid.getWildNode(oidStr)) {
                    result = MibNode::findByOid(newOid);
                }
            }
        } else {
            result = MibNode::findByOid(newOid);
        }
        if (type) *type = result.type();
        mibOid = newOid;
        if (!iid.isEmpty()) mibOid.concatOidStr(iid);
    } else if (oidStr.contains('.') || oidStr.contains(':')) { // if best_guess is off and multi part tag or module::tag
        MibOid newOid = MibOid::scanNumOid(oidStr); // make sure it's not a numeric tag
        if (!newOid.isValid()) {
            if (newOid.readObjid(oidStr)) { // long name
                result = MibNode::findByOid(newOid);
            }
        } else {
            result = MibNode::findByOid(newOid);
        }
        if (type) *type = result.type();
        mibOid = newOid;
        if (!iid.isEmpty()) mibOid.concatOidStr(iid);
    } else { // best_guess is off and it is a single leaf
        result = MibNode::findNode(oidStr);
        if (result.isValid()) {
            if (type) *type = result.type();
            mibOid = result.mibOid();
            if (!iid.isEmpty()) mibOid.concatOidStr(iid);
        }
    }
    return result;
}

/**********************************************************************/
/*!
 * \brief OidString::getLabelIid does a disection of <label1>...<labeln>.<iid> returning <labeln> and <iid> in seperate strings
 * \param name
 * \param lastLabel
 * \param iid
 * \param flag
 * \return success or not
 */
bool OidString::getLabelIid(const QString &name, QString &lastLabel, QString &iid, OidOptions flag)
{
    // TODO static int __get_label_iid _((char *, char **, char **, int));
    if (name.isEmpty()) {
        return false;
    }

    QStringList labels = name.split('.');

    if (flag.testFlag(UseNumericOids)) {
        if (!isNumericOid(name)) {
            return false;
        }
        if (labels.size() < 2) {
            return false;
        }
        iid = labels.takeLast();
        lastLabel = (flag.testFlag(UseLongNames)) ? labels.join('.') : labels.last();
        return true;
    }
    QRegularExpression re("[a-zA-Z]");
    int labelIdx = -1;
    for (int i=labels.size()-1; i>=0; --i) {
        if (labels.at(i).contains(re)) {
            labelIdx = i;
            break;
        }
    }
    if (labelIdx == -1) {
        return false;
    }
    if (flag.testFlag(FailOnNullOid)) {
        QString lbl = labels.last();
        re.setPattern("^\\d+$");
        QRegularExpressionMatch match = re.match(lbl);
        if (!match.hasMatch()) {
            return false;
        }
    }

    if (flag.testFlag(NonLeafName)) {
        /* dont know where to start instance id */
        /* put the whole thing in label */
        iid.clear();
        flag.setFlag(UseLongNames);
        if (labels.at(0).isEmpty() && labelIdx == 1) {
            /* special hack in case no mib loaded - object identifiers will
             * start with .iso.<num>.<num>...., in which case it is preferable
             * to make the label entirely numeric (i.e., convert "iso" => "1")
             */
            if (labels.at(1) == "ccitt") {
                labels.replace(1, "0");
            } else if (labels.at(1) == "iso") {
                labels.replace(1, "1");
            } if (labels.at(1) == "joint-iso-ccitt") {
                labels.replace(1, "2");
            }
        }

    } else {
        iid = labels.takeLast();
    }
    lastLabel = (flag.testFlag(UseLongNames)) ? labels.join('.') : labels.last();
    return true;
}

/**********************************************************************/

bool OidString::isNumericOid(const QString &name)
{
    OidString oidString(name);
    return oidString.isNumeric();
}

/**********************************************************************/

