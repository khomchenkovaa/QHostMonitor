#include "snmpobjectloader.h"

#include <QFile>

using namespace KharmonView;

/*************************************************************/

SnmpObjectLoader::SnmpObjectLoader(QObject *parent) : QObject(parent)
{

}

/*************************************************************/

void SnmpObjectLoader::create()
{
    m_FileName.clear();
    SnmpObject::SYSTEM.clear();
    SnmpObject::SUBSYSTEM.clear();
    SnmpObject::DLG_TIMEOUT = 10;
    if (SnmpObject::root != nullptr) {
        delete SnmpObject::root;
    }
    SnmpObject::root = new SnmpObject(this);
}

/*************************************************************/

void SnmpObjectLoader::load(const QString &fileName)
{
    if (fileName.isEmpty()) {
        create();
        return;
    }
    QFile file(fileName);
    if (!file.exists()) {
        emit loadFailed(tr("File '%1' does not exist").arg(fileName));
        return;
    }
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        emit loadFailed(file.errorString());
        return;
    }
    QString diagConf = file.readAll();
    file.close();
    if (!parseConf(diagConf)) {
        emit loadFailed(tr("File '%1' is not config").arg(fileName));
        return;
    }
    m_FileName = fileName;
}

/*************************************************************/

void SnmpObjectLoader::save(const QString &fileName)
{
    Q_UNUSED(fileName)
}

/*************************************************************/

bool SnmpObjectLoader::parseConf(const QString &diagConf)
{
    SnmpObject *root = new SnmpObject();
    SnmpObject *current = root;
    QString globalSystem, globalSubsystem;
    int globalTimeout = 10;
    int objLevel = 0;
    bool parseOK = true;
    QStringList confList = diagConf.split("\n", QString::SkipEmptyParts);
    foreach(const QString &confLine, confList) {
        QString line = confLine.trimmed();
        QString value;
        if (line.isEmpty() || line.startsWith("#")) continue;
        if (!objLevel) {
            value = valueForKey(line, "system");
            if (!value.isEmpty()) {
                globalSystem = value;
                continue;
            }
            value = valueForKey(line, "subsystem");
            if (!value.isEmpty()) {
                globalSubsystem = value;
                continue;
            }
            value = valueForKey(line, "dialog_timeout");
            if (!value.isEmpty()) {
                globalTimeout = value.toInt();
                continue;
            }
            if (current->setHostIfNotEmpty(valueForKey(line, "default_host"))) continue;
            if (current->setPortIfNotEmpty(valueForKey(line, "default_snmp_port"))) continue;
            if (current->setVersionIfNotEmpty(valueForKey(line, "default_snmp_version"))) continue;
            if (current->setCommunityIfNotEmpty(valueForKey(line, "default_snmp_community"))) continue;
            if (current->setTimeoutIfNotEmpty(valueForKey(line, "default_snmp_timeout"))) continue;
            if (current->setRetriesIfNotEmpty(valueForKey(line, "default_snmp_retries"))) continue;
        } else {
            if (current->setNameIfNotEmpty(valueForKey(line, "name"))) continue;
            if (current->setHostIfNotEmpty(valueForKey(line, "host"))) continue;
            if (current->setModuleIfNotEmpty(valueForKey(line, "module"))) continue;
            if (current->setPortIfNotEmpty(valueForKey(line, "snmp_port"))) continue;
            if (current->setVersionIfNotEmpty(valueForKey(line, "snmp_version"))) continue;
            if (current->setCommunityIfNotEmpty(valueForKey(line, "snmp_community"))) continue;
            if (current->setTimeoutIfNotEmpty(valueForKey(line, "snmp_timeout"))) continue;
            if (current->setRetriesIfNotEmpty(valueForKey(line, "snmp_retries"))) continue;
        }
        if (line.startsWith("}")) {
            SnmpObject *parentObj = qobject_cast<SnmpObject*>(current->parent());
            if (parentObj) current = parentObj;
            if (objLevel)  --objLevel;
            continue;
        }
        value = valueForKey(line, "object");
        if (value.startsWith("{")) {
            SnmpObject *childObj = new SnmpObject(current);
            current->append(childObj);
            current = childObj;
            ++objLevel;
            continue;
        }
    }

    parseOK = (objLevel == 0);

    if (parseOK) {
        SnmpObject::SYSTEM = globalSystem;
        SnmpObject::SUBSYSTEM = globalSubsystem;
        SnmpObject::DLG_TIMEOUT = globalTimeout;
        if (SnmpObject::root != nullptr) {
            delete SnmpObject::root;
        }
        SnmpObject::root = root;
    } else {
        root->deleteLater();
    }

    return parseOK;
}

/*************************************************************/

QString SnmpObjectLoader::valueForKey(const QString &line, const QString &key) const
{
    if (line.startsWith(key, Qt::CaseInsensitive)) {
        QString result = line.mid(key.length()).trimmed();
        if (result.startsWith("\"")) result.remove(0,1);
        if (result.endsWith("\"")) result.chop(1);
        return result;
    }
    return QString();
}

/*************************************************************/

