#include "netsnmptable.h"

/*****************************************************************/

SDPO::NetSnmpTable::NetSnmpTable(QObject *parent)
    : QObject(parent),
      ss(nullptr),
      pdu(nullptr)
{
    snmp_sess_init( &session );
}

/*****************************************************************/

SDPO::NetSnmpTable::~NetSnmpTable()
{
    if (ss) {
        snmp_close(ss);
    }
}

/*****************************************************************/

void SDPO::NetSnmpTable::setPeername(const QString &host)
{
    session.peername = strdup(host.toLatin1());
}

/*****************************************************************/

void SDPO::NetSnmpTable::setVersion(SDPO::SnmpVersion version)
{
    session.version = static_cast<long>(version);
}

/*****************************************************************/

void SDPO::NetSnmpTable::setCommunity(const QString &community)
{
    session.community = reinterpret_cast<u_char*>(community.toLocal8Bit().data());
    session.community_len = static_cast<size_t>(community.size());
}

/*****************************************************************/

void SDPO::NetSnmpTable::setTimeout(const int timeout)
{
    Q_UNUSED(timeout)
    // TODO set session.timeout
}

/*****************************************************************/

void SDPO::NetSnmpTable::setRetries(const int retries)
{
    session.retries = retries;
}

/*****************************************************************/

bool SDPO::NetSnmpTable::getColumns(const QString& oidStr)
{
    if (!snmp_parse_oid(oidStr.toLatin1(), root, &rootlen)) {
        return false;
    }
    MibTree *tbl = get_tree(root, rootlen, get_tree_head());
    if (tbl) { // get table entry
        tbl = tbl->child_list;
    }
    if (!tbl) { // no entry - not a table
        return false;
    }
    root[rootlen++] = tbl->subid; // add entry id
    tbl = tbl->child_list; // get first field
    if (!tbl) { // no fields - not a table
        return false;
    }

    do {
        if (tbl->access == MIB_ACCESS_NOACCESS) {
            continue;
        }
        SnmpColumn* col = new SnmpColumn();
        col->subid = tbl->subid;
        col->label = QString(tbl->label);
        columns.prepend(col);
    } while ((tbl = tbl->next_peer));

    return true;
}

QStringList SDPO::NetSnmpTable::getTableEntries()
{
    QStringList result;
    SnmpPdu *pduResponse;
    oid      name[MAX_OID_LEN];
    size_t   namelen = rootlen + 1;
    for (size_t i=0; i<rootlen; ++i) {
        name[i] = root[i];
    }

    // while (!end of table)

    // create pdu with column ids
    pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
    for (int i = 0; i <= columns.size(); i++) {
        name[rootlen] = columns.at(i)->subid;
        snmp_add_null_var(pdu, name, namelen);
    }

    SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

    if (status == SnmpRespStatSuccess) {
        if (pduResponse->errstat == SNMP_ERR_NOERROR) {
            for(netsnmp_variable_list *vars = pduResponse->variables; vars != nullptr; vars = vars->next_variable) {
                result << NetSNMP::valueFrom(vars).toString();
            }
        } else {
            result << snmp_errstring(static_cast<int>(pduResponse->errstat));
        }
    } else if (status == SnmpRespStatTimeout) {
        result << QString("Timeout: No Response from %1.").arg(session.peername);
    } else {                    /* status == SnmpRespStatError */
        result << QString("Error in Response from %1.").arg(session.peername);
        // snmp_sess_perror("snmpget", ss);
    }

    if (pduResponse) {
      snmp_free_pdu(pduResponse);
    }

    return result;
}

/*****************************************************************/
