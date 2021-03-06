#include "snmpobject.h"

#include <QDebug>

using namespace KharmonView;

/*************************************************************/

QString SnmpObject::SYSTEM;
QString SnmpObject::SUBSYSTEM;
int SnmpObject::DLG_TIMEOUT = 10;
SnmpObject* SnmpObject::root = nullptr;

/*************************************************************/

SnmpObject::SnmpObject(QObject *parent)
    : QObject(parent),
    m_TimerId(0)
{

}

/*************************************************************/

void SnmpObject::append(SnmpObject *child)
{
    child->setParent(this);
    m_Objects.append(child);
    connect(child, &SnmpObject::snmpUpdate, this, &SnmpObject::snmpUpdate);
}

/*************************************************************/

void SnmpObject::remove(SnmpObject *child)
{
    if (m_Objects.removeOne(child)) {
        child->deleteLater();
    }
}

/*************************************************************/

SnmpObject *SnmpObject::parentObj()
{
    return qobject_cast<SnmpObject*>(parent());
}

/*************************************************************/

void SnmpObject::clearVars()
{
    m_Host.clear();
    m_ModIdx.clear();
    m_Port.clear();
    m_Version.clear();
    m_Community.clear();
    m_Timeout.clear();
    m_Retries.clear();
}

/*************************************************************/

QString SnmpObject::getName() const
{
    return m_Name;
}

/*************************************************************/

int SnmpObject::getModIdx() const
{
    if (m_ModIdx.isValid()) {
        return m_ModIdx.toInt();
    }
    return 0;
}

/*************************************************************/

QString SnmpObject::getHost() const
{
    if (m_Host.isValid()) {
        return m_Host.toString();
    }
    if (root && root->m_Host.isValid()) {
        return root->m_Host.toString();
    }
    return DFLT_HOST;
}

/*************************************************************/

int SnmpObject::getPort() const
{
    if (m_Port.isValid()) {
        return m_Port.toInt();
    }
    if (root && root->m_Port.isValid()) {
        return root->m_Port.toInt();
    }
    return DFLT_SNMP_PORT;
}

/*************************************************************/

QString SnmpObject::getDestHost() const
{
    return QString("%1:%2").arg(getHost()).arg(getPort());
}

/*************************************************************/

SDPO::SnmpVersion SnmpObject::getVersion() const
{
    if (m_Version.isValid()) {
        return static_cast<SDPO::SnmpVersion>(m_Version.toInt());
    }
    if (root && root->m_Version.isValid()) {
        return static_cast<SDPO::SnmpVersion>(root->m_Version.toInt());
    }
    return DFLT_SNMP_VERSION;
}

/*************************************************************/

QString SnmpObject::getVersionStr() const
{
    switch (getVersion()) {
    case SDPO::SNMPv1:  return "1";
    case SDPO::SNMPv2c: return "2c";
    case SDPO::SNMPv3:  return "3";
    default: break;
    }
    return "2c";
}

/*************************************************************/

QString SnmpObject::getCommunity() const
{
    if (m_Community.isValid()) {
        return m_Community.toString();
    }
    if (root && root->m_Community.isValid()) {
        return root->m_Community.toString();
    }
    return DFLT_SNMP_COMMUNITY;
}

/*************************************************************/

int SnmpObject::getTimeout() const
{
    if (m_Timeout.isValid()) {
        return m_Timeout.toInt();
    }
    if (root && root->m_Timeout.isValid()) {
        return root->m_Timeout.toInt();
    }
    return DFLT_SNMP_TIMEOUT;
}

/*************************************************************/

int SnmpObject::getRetries() const
{
    if (m_Retries.isValid()) {
        return m_Retries.toInt();
    }
    if (root && root->m_Retries.isValid()) {
        return root->m_Retries.toInt();
    }
    return DFLT_SNMP_RETRIES;
}

/*************************************************************/

bool SnmpObject::setNameIfNotEmpty(const QString &value)
{
    if (!value.isEmpty()) {
        setName(value);
        return true;
    }
    return false;
}

/*************************************************************/

bool SnmpObject::setHostIfNotEmpty(const QString &value)
{
    if (!value.isEmpty()) {
        setHost(value);
        return true;
    }
    return false;
}

/*************************************************************/

bool SnmpObject::setPortIfNotEmpty(const QString &value)
{
    if (!value.isEmpty()) {
        bool ok;
        int port = value.toInt(&ok);
        if (ok) {
            setPort(port);
            return true;
        }
    }
    return false;
}

/*************************************************************/

bool SnmpObject::setVersionIfNotEmpty(const QString &value)
{
    if (!value.isEmpty()) {
        bool ok;
        int version = value.toInt(&ok);
        if (ok) {
            switch(version) {
            case 1: setVersion(SDPO::SNMPv1); break;
            case 2: setVersion(SDPO::SNMPv2c); break;
            case 3: setVersion(SDPO::SNMPv3); break;
            default: setVersion(SDPO::SNMPvDefault); break;
            }
            return true;
        }
    }
    return false;
}

/*************************************************************/

bool SnmpObject::setCommunityIfNotEmpty(const QString &value)
{
    if (!value.isEmpty()) {
        setCommunity(value);
        return true;
    }
    return false;
}

/*************************************************************/

bool SnmpObject::setTimeoutIfNotEmpty(const QString &value)
{
    if (!value.isEmpty()) {
        bool ok;
        int timeout = value.toInt(&ok);
        if (ok) {
            setTimeout(timeout);
            return true;
        }
    }
    return false;
}

/*************************************************************/

bool SnmpObject::setRetriesIfNotEmpty(const QString &value)
{
    if (!value.isEmpty()) {
        bool ok;
        int retries = value.toInt(&ok);
        if (ok) {
            setRetries(retries);
            return true;
        }
    }
    return false;
}

/*************************************************************/

bool SnmpObject::setModuleIfNotEmpty(const QString &value)
{
    if (!value.isEmpty()) {
        bool ok;
        int modIdx = value.toInt(&ok);
        if (ok) {
            setModIdx(modIdx);
            return true;
        }
    }
    return false;
}

/*************************************************************/

void SnmpObject::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    updateWithChilds();
}

/*************************************************************/

void SnmpObject::updateWithChilds()
{
    if (!m_Name.isEmpty()) { // ROOT
        emit snmpUpdate(this);
    }
    foreach(SnmpObject* obj, m_Objects) {
        obj->updateWithChilds();
    }
}

/*************************************************************/

void SnmpObject::startView()
{
    if (m_TimerId == 0) {
        m_TimerId = startTimer(DLG_TIMEOUT * 1000, Qt::VeryCoarseTimer);
    }
}

/*************************************************************/

void SnmpObject::stopView()
{
    if (m_TimerId != 0) {
        killTimer(m_TimerId);
        m_TimerId = 0;
    }
}

/*************************************************************/
