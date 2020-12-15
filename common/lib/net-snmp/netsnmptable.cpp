#include "netsnmptable.h"

#include <QDebug>

/*****************************************************************/

SDPO::NetSnmpTable::NetSnmpTable(QObject *parent)
    : NetSnmpCommon(parent)
{
}

/*****************************************************************/

SDPO::NetSnmpTable::~NetSnmpTable()
{
    // clear columns
    qDeleteAll(m_Columns);
    m_Columns.clear();
}

/*****************************************************************/

QList<SDPO::SnmpColumn*> SDPO::NetSnmpTable::readColumns(const QString& oidStr)
{
    // clear columns
    qDeleteAll(m_Columns);
    m_Columns.clear();

    if (!snmp_parse_oid(oidStr.toLatin1(), m_Root, &m_RootLen)) {
        int xerr = snmp_errno;
        const char *str = snmp_api_errstring(xerr);
        qDebug() << oidStr << ": " << str;
        return m_Columns;
    }
    MibTree *tbl = get_tree(m_Root, m_RootLen, get_tree_head());
    if (tbl) { // get table entry
        tbl = tbl->child_list;
    }
    if (!tbl) { // no entry - not a table
        return m_Columns;
    }
    m_Root[m_RootLen++] = tbl->subid; // add entry id
    tbl = tbl->child_list; // get first field
    if (!tbl) { // no fields - not a table
        return m_Columns;
    }

    do {
        if (tbl->access == MIB_ACCESS_NOACCESS) {
            continue;
        }
        SnmpColumn* col = new SnmpColumn();
        col->subid = tbl->subid;
        col->label = QString(tbl->label);
        m_Columns.prepend(col);
    } while ((tbl = tbl->next_peer));

    return m_Columns;
}

/*****************************************************************/

QList<QList<SDPO::SnmpValue>> SDPO::NetSnmpTable::getTableEntries()
{
    QList<QList<SDPO::SnmpValue>> result;

    // Initialize a "session" that defines who we're going to talk to
    SnmpSession session;
    snmpSessionInit( &session );

    oid      name[MAX_OID_LEN];
    size_t   namelen = m_RootLen + 1;
    for (size_t i=0; i<m_RootLen; ++i) {
        name[i] = m_Root[i];
    }

    SOCK_STARTUP;
    SnmpSession *ss = snmp_open(&session); // establish the session
    if (!ss) {
        snmpSessionLogError(LOG_ERR, "ack", &session);
        SOCK_CLEANUP;
        return result;
    }

    bool running = true;
    int entries = 0;
    const int MaxEntries = 20;
    // while (!end of table) {
    while (running && (entries < MaxEntries)) {

        // create pdu with column ids
        SnmpPdu *pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
        for (int i = 0; i < m_Columns.size(); i++) {
            name[m_RootLen] = m_Columns.at(i)->subid;
            snmp_add_null_var(pdu, name, namelen);

        }

        SnmpPdu *pduResponse = nullptr;
        SnmpResponseStatus status = static_cast<SnmpResponseStatus>(snmp_synch_response(ss, pdu, &pduResponse));

        if (status == SnmpRespStatSuccess) {
            if (pduResponse->errstat == SNMP_ERR_NOERROR) {
                netsnmp_variable_list *vars = pduResponse->variables;
                if (!entries) {
                    namelen++;
                } else {
                    if ((namelen != vars->name_length) || (name[namelen-1] >= vars->name[namelen-1])) {
                        running = false;
                    }
                }
                if (running) {
                    name[namelen-1] = vars->name[namelen-1];
                    entries++;
                    QList<SDPO::SnmpValue> entry;
                    for(; vars != nullptr; vars = vars->next_variable) {
                        entry.append(SnmpValue::fromVar(vars));
                    }
                    result.append(entry);
                }
            } else if (pduResponse->errstat == SNMP_ERR_NOSUCHNAME) {
                running = false; // end of table
            } else {
                qDebug() << snmp_errstring(static_cast<int>(pduResponse->errstat));
                running = false;
            }
        } else if (status == SnmpRespStatTimeout) {
            qDebug() << QString("Timeout: No Response from %1.").arg(session.peername);
            running = false;
        } else {                    /* status == SnmpRespStatError */
            qDebug() << QString("Error in Response from %1.").arg(session.peername);
            snmpSessionLogError(LOG_ERR, "GETNEXT", &session);
            running = false;
        }

        if (pduResponse) {
          snmp_free_pdu(pduResponse);
        }

    }

    snmp_close(ss);
    SOCK_CLEANUP;

    return result;
}

/*****************************************************************/
