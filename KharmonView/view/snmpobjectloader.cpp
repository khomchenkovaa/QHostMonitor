#include "snmpobjectloader.h"

#include <QFile>
#include <QFileInfo>

using namespace KharmonView;

/*************************************************************/

SnmpObjectLoader::SnmpObjectLoader(QObject *parent)
    : QObject(parent)
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
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        emit saveFailed(file.errorString());
        return;
    }

    QFileInfo fi(file);
    UnicodedStream out(&file);
    out.setCodec("UTF-8");
    out << "################################################################################" << endl;
    out << "# " << fi.fileName() << endl;
    out << "# ПО для диагностики ПТС. Файл конфигурации для программ отображения" << endl;
    out << "# диагностической информации (SNMP-менеджеров)." << endl;
    out << "################################################################################" << endl;
    out << endl;
    out << "## Обязательные параметры отмечены знаком (*), остальные параметры могут" << endl;
    out << "## отсутствовать." << endl;
    out << "## Значения по умолчанию для параметров, не указанные в данном конфигурационном" << endl;
    out << "## файле, определены непосредственно в соответствующей программе отображения" << endl;
    out << "## диагностической информации." << endl;
    out << endl;
    out << "################################################################################" << endl;
    out << "## Общие параметры" << endl;
    out << "################################################################################" << endl;
    out << endl;
    out << "## Наименование контролируемой системы." << endl;
    out << "system \"" << SnmpObject::SYSTEM << "\"" << endl;
    out << endl;
    out << "## Наименование контролируемого объекта верхнего уровня." << endl;
    out << "subsystem \"" << SnmpObject::SUBSYSTEM << "\"" << endl;
    out << endl;
    out << "## Интервал основного цикла опроса сценария diag-view.pl в сек." << endl;
    out << "## (по умолчанию: 10 сек.)." << endl;
    out << "dialog_timeout " << SnmpObject::DLG_TIMEOUT << endl;
    out << endl;
    out << "################################################################################" << endl;
    out << "## Параметры по умолчанию для связи с SNMP-агентами." << endl;
    out << "##" << endl;
    out << "## Сетевое имя или IP-адрес узла (по умолчанию: localhost)." << endl;
    out << "## default_host <host>" << endl;
    if (SnmpObject::root &&  SnmpObject::root->isHostValid()) {
        out << "default_host " << SnmpObject::root->getHost() << endl;
    }
    out << "##" << endl;
    out << "## Номер порта (по умолчанию 161)." << endl;
    out << "## default_snmp_port <port>" << endl;
    if (SnmpObject::root &&  SnmpObject::root->isPortValid()) {
        out << "default_host " << SnmpObject::root->getPort() << endl;
    }
    out << "##" << endl;
    out << "## Версия протокола SNMP (по умолчанию 2)." << endl;
    out << "## default_snmp_version <1|2>" << endl;
    if (SnmpObject::root &&  SnmpObject::root->isVersionValid()) {
        out << "default_host " << SnmpObject::root->getVersion() << endl;
    }
    out << "##" << endl;
    out << "## Имя SNMP-сообщества (по умолчанию: public)." << endl;
    out << "## default_snmp_community <community>" << endl;
    if (SnmpObject::root &&  SnmpObject::root->isCommunityValid()) {
        out << "default_host " << SnmpObject::root->getCommunity() << endl;
    }
    out << "##" << endl;
    out << "## Масксимальный интервал ожидания ответа от SNMP-агента, в сек." << endl;
    out << "## (по умолчанию: 1 сек.)." << endl;
    out << "## default_snmp_timeout <timeout>" << endl;
    if (SnmpObject::root &&  SnmpObject::root->isTimeoutValid()) {
        out << "default_host " << SnmpObject::root->getTimeout() << endl;
    }
    out << "##" << endl;
    out << "## Максимальное количество повторных SNMP-запросов в случае неудачи" << endl;
    out << "## (по умолчанию: 3)." << endl;
    out << "## default_snmp_retries <retries>" << endl;
    if (SnmpObject::root &&  SnmpObject::root->isRetriesValid()) {
        out << "default_host " << SnmpObject::root->getRetries() << endl;
    }
    out << endl;
    out << "################################################################################" << endl;
    out << "## Формат конфигурационной информации для диагностики." << endl;
    out << "################################################################################" << endl;
    out << "##" << endl;
    out << "## Диагностическая информация представляет собой множество контролируемых объектов," << endl;
    out << "## объединённых в иерархическую структуру с произвольным уровнем вложенности." << endl;
    out << "##" << endl;
    out << "################################################################################" << endl;
    out << "## Формат описания иерархии контролируемых объектов." << endl;
    out << "##" << endl;
    out << "## object {" << endl;
    out << "##" << endl;
    out << "##		 <object options>" << endl;
    out << "##" << endl;
    out << "##		 object {" << endl;
    out << "##			<object options>" << endl;
    out << "##		 }" << endl;
    out << "##" << endl;
    out << "##		. . ." << endl;
    out << "##" << endl;
    out << "##		object {" << endl;
    out << "##			<object options>" << endl;
    out << "##		}" << endl;
    out << "## }" << endl;
    out << "##" << endl;
    out << "## <object options> - опции контролируемого объекта" << endl;
    out << "##" << endl;
    out << "################################################################################" << endl;
    out << "## Формат опций контролируемого объекта." << endl;
    out << "##" << endl;
    out << "## object {" << endl;
    out << "##" << endl;
    out << "##	name <name> (*)				- Наименование контролируемого объекта." << endl;
    out << "##" << endl;
    out << "## Параметры для связи с SNMP-агентом:" << endl;
    out << "##" << endl;
    out << "##	host <host>					- Сетевое имя или IP-адрес узла." << endl;
    out << "##" << endl;
    out << "##	module <module index>		- Индекс модуля, начиная с 1." << endl;
    out << "##" << endl;
    out << "##	snmp_port <port>			- Номер порта." << endl;
    out << "##" << endl;
    out << "##	snmp_version <1|2>			- Версия протокола SNMP." << endl;
    out << "##" << endl;
    out << "##	snmp_community <community>	- Имя SNMP-сообщества." << endl;
    out << "##" << endl;
    out << "##	snmp_timeout <timeout>		- Максимальный интервал ожидания ответа от" << endl;
    out << "##								  SNMP-агента, в сек." << endl;
    out << "##" << endl;
    out << "##	snmp_retries <retries>		- Максимальное количество повторных SNMP-запросов" << endl;
    out << "##								  в случае неудачи." << endl;
    out << "##" << endl;
    out << "##	}" << endl;
    out << "##" << endl;
    out << endl;
    out << "################################################################################" << endl;
    out << "# Описание контролируемых объектов." << endl;
    out << "################################################################################" << endl;

    if (SnmpObject::root) {
        foreach(SnmpObject *child, *SnmpObject::root->snmpObjects()) {
            out << endl;
            printObject(out, child);
        }
    }
    file.close();
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

void SnmpObjectLoader::printObject(UnicodedStream &out, SnmpObject *node, int tab)
{
//    QString tabStr(' ', tab);
//    QString tab2Str(' ', tab + 4);
    QString tabStr;
    for (int i=0; i<tab; i++) tabStr.append(" ");
    QString tab2Str(tabStr);
    for (int i=0; i<4; i++) tab2Str.append(" ");
    out << tabStr << "object {" << endl;
    out << tab2Str << "name \"" << node->getName() << "\"" << endl;
    if (node->isHostValid()) {
        out << tab2Str << "host " << node->getHost() << endl;
    }
    if (node->getModIdx()) {
        out << tab2Str << "module " << node->getModIdx() << endl;
    }
    if (node->isPortValid()) {
        out << tab2Str << "snmp_port " << node->getPort() << endl;
    }
    if (node->isVersionValid()) {
        out << tab2Str << "snmp_version " << node->getVersion() << endl;
    }
    if (node->isCommunityValid()) {
        out << tab2Str << "snmp_community " << node->getCommunity() << endl;
    }
    if (node->isTimeoutValid()) {
        out << tab2Str << "snmp_timeout " << node->getTimeout() << endl;
    }
    if (node->isRetriesValid()) {
        out << tab2Str << "snmp_retries " << node->getRetries() << endl;
    }
    foreach(SnmpObject *child, *node->snmpObjects()) {
        out << endl;
        printObject(out, child, tab + 4);
    }
    out << tabStr << "}" << endl;
}

/*************************************************************/

