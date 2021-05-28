#include "snmpresultwidget.h"

#include <QHeaderView>

using namespace KharmonView;

/*************************************************************/

SnmpResultWidget::SnmpResultWidget(QWidget *parent) : QTreeWidget(parent)
{
    setupUI();
}

/*************************************************************/

void SnmpResultWidget::setSnmpObject(SnmpObject *node)
{
    clear();

    if (node == nullptr) {
        return;
    }

    if (node->getModIdx()) {
        for (int i=0; i< node->snmpModList()->size(); ++i) {
            if (node->snmpModList()->at(i).modIndex == node->getModIdx()) {
                setModuleInfo(&(node->snmpModList()->at(i)));
                QString paramInfo = tr("Parameters");
                QTreeWidgetItem *parent = new QTreeWidgetItem(QStringList() << paramInfo);
                addTopLevelItem(parent);
                QFont font = parent->font(0);
                font.setBold(true);
                parent->setFont(0, font);
                setParamList(parent, node->snmpParamList(), node->getModIdx());
                setFirstItemColumnSpanned(parent, true);
                parent->setExpanded(true);
                break;
            }
        }
    } else {
        setSysInfo(node->snmpSystem());
        setStatInfo(node->snmpStatus());
        if (!node->snmpModList()->isEmpty()) {
            setModuleList(node->snmpModList(), node->snmpParamList());
        }
    }
}

/*************************************************************/

void SnmpResultWidget::updateSnmpObject(SnmpObject *node)
{
    setSnmpObject(node);
}

/*************************************************************/

void SnmpResultWidget::setupUI()
{
    setObjectName(QStringLiteral("ObjectInfo"));

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);

    QFont font;
    font.setPointSize(9);

    QString styleSheet =
        "QTreeWidget::item:!selected { "
        "border: 1px solid gainsboro; "
        "border-left: none; "
        "border-top: none; "
        "} "
        "QTreeView::item:selected {}";

    setStyleSheet(styleSheet);
    setAlternatingRowColors(true);
    setColumnCount(3);
    setColumnWidth(0, 150);
    setColumnWidth(0, 300);
    setMinimumWidth(600);
    setHeaderLabels(QStringList() << "Атрибут" << "Значение" << "Статус");
    setFont(font);
    header()->setFont(font);
}

/*************************************************************/

void SnmpResultWidget::setSysInfo(const SnmpSystem *info)
{
    QString sysInfo = tr("System Info");
    QString sysName = tr("Name");
    QString sysDescr = tr("Description");
    QString sysLocation = tr("Location");
    QString sysContact = tr("Contact");
    QString sysType = tr("Type");
    QString sysParentUri = tr("Parent URI");

    QTreeWidgetItem *parent = new QTreeWidgetItem(QStringList() << sysInfo);
    addTopLevelItem(parent);
    QFont font = parent->font(0);
    font.setBold(true);
    parent->setFont(0, font);

    parent->addChild(new QTreeWidgetItem(QStringList() << sysName << info->sysName));
    parent->addChild(new QTreeWidgetItem(QStringList() << sysDescr << info->sysDescr));
    if (!info->sysLocation.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << sysLocation << info->sysLocation));
    }
    if (!info->sysContact.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << sysContact << info->sysContact));
    }
    parent->addChild(new QTreeWidgetItem(QStringList() << sysType << typeAsText(info->sysType)));
    if (!info->sysParentObjectURI.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << sysParentUri << info->sysParentObjectURI));
    }

    setFirstItemColumnSpanned(parent, true);
    parent->setExpanded(true);
}

/*************************************************************/

void SnmpResultWidget::setStatInfo(const SnmpStatus *info)
{
    QString statInfo = tr("Status Info");
    QString statStatus = tr("Status");
    QString statStatusDescr = tr("Status Description");
    QString statLastChangeDate = tr("Last Change Date");

    QTreeWidgetItem *parent = new QTreeWidgetItem(QStringList() << statInfo);
    addTopLevelItem(parent);
    QFont font = parent->font(0);
    font.setBold(true);
    parent->setFont(0, font);

    parent->addChild(new QTreeWidgetItem(QStringList() << statStatus << statusAsText(info->statStatus)));
    parent->addChild(new QTreeWidgetItem(QStringList() << statStatusDescr << info->statStatusDesc));
    parent->addChild(new QTreeWidgetItem(QStringList() << statLastChangeDate << info->statLastChangeDate));

    setColorByStatus(parent->child(0), 1, info->statStatus);
    setColorByStatus(parent->child(1), 1, info->statStatus);

    setFirstItemColumnSpanned(parent, true);
    parent->setExpanded(true);
}

/*************************************************************/

void SnmpResultWidget::setModuleInfo(const SnmpModule *info)
{
    QString modInfo = tr("Module Info");
    QString modName = tr("Name");
    QString modDesc = tr("Description");
    QString modType = tr("Type");
    QString modStatus = tr("Status");
    QString modStatusDescr = tr("Status Description");
    QString modLastChangeDate = tr("Last Change Date");
    QString modUri = tr("URI");
    QString modIndex = tr("Index");

    QTreeWidgetItem *parent = new QTreeWidgetItem(QStringList() << modInfo);
    addTopLevelItem(parent);
    QFont font = parent->font(0);
    font.setBold(true);
    parent->setFont(0, font);

    parent->addChild(new QTreeWidgetItem(QStringList() << modName << info->modName));
    parent->addChild(new QTreeWidgetItem(QStringList() << modDesc << info->modDesc));
    parent->addChild(new QTreeWidgetItem(QStringList() << modType << typeAsText(info->modType)));
    parent->addChild(new QTreeWidgetItem(QStringList() << modStatus << statusAsText(info->modStatus)));
    parent->addChild(new QTreeWidgetItem(QStringList() << modStatusDescr << info->modStatusDesc));
    parent->addChild(new QTreeWidgetItem(QStringList() << modLastChangeDate << info->modLastChangeDate));
    if (!info->modURI.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << modUri << info->modURI));
    }
    parent->addChild(new QTreeWidgetItem(QStringList() << modIndex << QString::number(info->modIndex)));

    setColorByStatus(parent->child(3), 1, info->modStatus);
    setColorByStatus(parent->child(4), 1, info->modStatus);

    setFirstItemColumnSpanned(parent, true);
    parent->setExpanded(true);
}

/*************************************************************/

void SnmpResultWidget::setModuleList(const SnmpModList *modList, const SnmpParamList *paramList)
{
    QString modInfo = tr("Modules");
    QTreeWidgetItem *parent = new QTreeWidgetItem(QStringList() << modInfo);
    addTopLevelItem(parent);
    QFont font = parent->font(0);
    font.setBold(true);
    parent->setFont(0, font);

    foreach(const SnmpModule &info, *modList) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, info.modDesc);
        item->setText(1, info.modStatusDesc);
        item->setText(2, statusAsText(info.modStatus));
        item->setIcon(0, iconByModStatus(info.modStatus));
        setColorByStatus(item, 1, info.modStatus);
        setColorByStatus(item, 2, info.modStatus);
        parent->addChild(item);
        setParamList(item, paramList, info.modIndex);
    }
    setFirstItemColumnSpanned(parent, true);
    parent->setExpanded(true);
}

/*************************************************************/

void SnmpResultWidget::setParamInfo(QTreeWidgetItem *parent, const SnmpParameter *info)
{
    QString paramName = tr("Name");
    QString paramDesc = tr("Description");
    QString paramCurrValue = tr("Current Value");
    QString paramCurrValueDesc = tr("Description of current value");
    QString paramUnits = tr("Units");
    QString paramStatus = tr("Status");
    QString paramLastChangeDate = tr("Date of Last Change");
    QString paramNormalValue = tr("Normal Value");
    QString paramLowFailLimit = tr("Low Failure Limit");
    QString paramLowWarningLimit = tr("Low Warning Limit");
    QString paramHighFailLimit = tr("High Failure Limit");
    QString paramHighWarningLimit = tr("High Warning Limit");

    parent->addChild(new QTreeWidgetItem(QStringList() << paramName << info->paramName));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramDesc << info->paramDesc));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramCurrValue << info->paramCurrValue));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramCurrValueDesc << info->paramCurrValueDesc));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramUnits << info->paramUnits));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramStatus << statusAsText(info->paramStatus)));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramLastChangeDate << info->paramLastChangeDate));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramNormalValue << info->paramNormalValue));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramLowFailLimit << info->paramLowFailLimit));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramLowWarningLimit << info->paramLowWarningLimit));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramHighFailLimit << info->paramHighFailLimit));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramHighWarningLimit << info->paramHighWarningLimit));

    setColorByStatus(parent->child(2), 1, info->paramStatus);
    setColorByStatus(parent->child(5), 1, info->paramStatus);
}

/*************************************************************/

void SnmpResultWidget::setParamList(QTreeWidgetItem *parent, const SnmpParamList *paramList, int modIdx)
{
    foreach(const SnmpParameter &info, *paramList) {
        if (info.paramModuleIndex != modIdx) continue;
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, info.paramDesc);
        item->setText(1, paramValue(info));
        item->setText(2, statusAsText(info.paramStatus));
        item->setIcon(0, iconByParamStatus(info.paramStatus));
        setColorByStatus(item, 1, info.paramStatus);
        setColorByStatus(item, 2, info.paramStatus);
        parent->addChild(item);
        setParamInfo(item, &info);
    }
}

/*************************************************************/

QIcon SnmpResultWidget::iconByModStatus(const int status) const
{
    switch (status) {
    case 0: // normal
        return QIcon(":img/status/tstHostAlive.png");
    case 1: // lowWarning
    case 2: // highWarning
        return QIcon(":img/status/tstWaitForMaster.png");
    case 3: // initial
        return QIcon(":img/status/tstChecking.png");
    case 10: // lowFail
    case 11: // highFail
    case 12: // fail
        return QIcon(":img/status/tstNoAnswer.png");
    case 101: // unknown
        return QIcon(":img/status/tstUnknown.png");
    }
    return QIcon();
}

/*************************************************************/

QIcon SnmpResultWidget::iconByParamStatus(const int status) const
{
    switch (status) {
    case 0: // normal
        return QIcon(":img/status/tstOk.png");
    case 1: // lowWarning
    case 2: // highWarning
        return QIcon(":img/status/tstBadContents.png");
    case 3: // initial
        return QIcon(":img/status/tstChecking.png");
    case 10: // lowFail
    case 11: // highFail
    case 12: // fail
        return QIcon(":img/status/tstBad.png");
    case 101: // unknown
        return QIcon(":img/status/tstNotTested.png");
    }
    return QIcon();
}

/*************************************************************/

QString SnmpResultWidget::statusAsText(const int status) const
{
    switch (status) {
    case 0: // normal
        return tr("NORMAL");
    case 1: // lowWarning
        return tr("LOW WARNING");
    case 2: // highWarning
        return tr("HIGH WARNING");
    case 3: // initial
        return tr("INITIAL");
    case 10: // lowFail
        return tr("LOW FAIL");
    case 11: // highFail
        return tr("HIGH FAIL");
    case 12: // fail
        return tr("FAIL");
    case 101: // unknown
        return tr("UNKNOWN");
    }
    return tr("Not defined");
}

/*************************************************************/

QString SnmpResultWidget::typeAsText(const int sysType) const
{
    switch (sysType) {
    case  1: return "системный модуль (SystemModule)";
    case  2: return "система питания (PowerSystem)";
    case  3: return "коммутатор ЛВС (NetworkSwitch)";
    case  4: return "сетевой маршрутизатор/шлюз (NetworkRouter)";
    case  5: return "межсетевой экран (Firewall)";
    case  6: return "сервер точного времени (TimeServer)";
    case  7: return "преобразователь/конвертер ЛВС (NetworkConverter)";
    case  8: return "блок контроля шкафа (RMS)";
    case  9: return "блок диагностики (DiagUnit)";
    case 10: return "источник бесперебойного питания (UPS)";
    case 11: return "система хранения данных (StorageSystem)";
    case 12: return "сервер (Server)";
    case 13: return "рабочая станция (Workstation)";
    case 14: return "серверная стойка (ServerRack)";
    case 15: return "система (System)";
    case 16: return "подсистема (SubSystem)";
    case 17: return "системный программный модуль (SysSoftwareModule)";
    case 18: return "прикладной программный модуль (AppSoftwareModule)";
    case 19: return "служба (SoftwareService)";
    case 20: return "системная плата (SystemBoard)";
    case 21: return "датчики температуры (TemperatureSensors)";
    case 22: return "сетевая система (NetworkSystem)";
    case 23: return "операционная система (OperatingSystem)";
    case 24: return "система охлаждения (CoolingSystem)";
    case 25: return "датчики (Sensors)";
    }
    return "другой";
}

/*************************************************************/

QString SnmpResultWidget::paramValue(const SnmpParameter &info)
{
    QString units;
    if (info.paramDataType == 2) {
        units = info.paramUnits;
    }
    if (units == "Percent") {
        units = "%";
    }
    if (units == "text") {
        units.clear();
    }

    switch (info.paramStatus) {
    case 0: // normal
        return QString("%1 %2").arg(info.paramCurrValue, units);
    case 1: // lowWarning
        return QString("%1 %2 (%3 %4)").arg(info.paramCurrValue, units, info.paramLowWarningLimit, units);
    case 2: // highWarning
        return QString("%1 %2 (%3 %4)").arg(info.paramCurrValue, units, info.paramHighWarningLimit, units);
    case 3: // initial
        break;
    case 10: // lowFail
        return QString("%1 %2 (%3 %4)").arg(info.paramCurrValue, units, info.paramLowFailLimit, units);
    case 11: // highFail
        return QString("%1 %2 (%3 %4)").arg(info.paramCurrValue, units, info.paramHighFailLimit, units);
    case 12: // fail
        return QString("%1 %2 (%3 %4)").arg(info.paramCurrValue, units, info.paramNormalValue, units);
    case 101: // unknown
        return info.paramCurrValueDesc;
    }
    return QString();
}

/*************************************************************/

void SnmpResultWidget::setColorByStatus(QTreeWidgetItem *item, const int column, const int status)
{
    QBrush brush = item->foreground(column);
    switch (status) {
    case 0: // normal
        brush.setColor(Qt::darkGreen);
        break;
    case 1: // lowWarning
    case 2: // highWarning
        brush.setColor(Qt::darkBlue);
        break;
    case 3: // initial
        brush.setColor(Qt::darkGray);
        break;
    case 10: // lowFail
    case 11: // highFail
    case 12: // fail
    case 101: // unknown
        brush.setColor(Qt::darkRed);
        break;
    }
    item->setForeground(column, brush);
}

/*************************************************************/
