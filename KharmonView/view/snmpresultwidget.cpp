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
    parent->addChild(new QTreeWidgetItem(QStringList() << sysType << QString::number(info->sysType)));
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
    parent->addChild(new QTreeWidgetItem(QStringList() << modType << QString::number(info->modType)));
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
    QString paramCurrValue = tr("Curr Value");
    QString paramCurrValueDesc = tr("Curr Value Desc");
    QString paramType = tr("Type");
    QString paramDataType = tr("Data Type");
    QString paramUnits = tr("Units");
    QString paramStatus = tr("Status");
    QString paramLastChangeDate = tr("Last Change Date");
    QString paramNormalValue = tr("Normal Value");
    QString paramLowFailLimit = tr("Low Fail Limit");
    QString paramLowWarningLimit = tr("Low Warning Limit");
    QString paramHighFailLimit = tr("High Fail Limit");
    QString paramHighWarningLimit = tr("High Warning Limit");
    QString paramModuleIndex = tr("Module Index");

    parent->addChild(new QTreeWidgetItem(QStringList() << paramName << info->paramName));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramDesc << info->paramDesc));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramCurrValue << info->paramCurrValue));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramCurrValueDesc << info->paramCurrValueDesc));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramType << QString::number(info->paramType)));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramDataType << QString::number(info->paramDataType)));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramUnits << info->paramUnits));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramStatus << statusAsText(info->paramStatus)));
    parent->addChild(new QTreeWidgetItem(QStringList() << paramLastChangeDate << info->paramLastChangeDate));
    if (!info->paramNormalValue.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << paramNormalValue << info->paramNormalValue));
    }
    if (!info->paramLowFailLimit.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << paramLowFailLimit << info->paramLowFailLimit));
    }
    if (!info->paramLowWarningLimit.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << paramLowWarningLimit << info->paramLowWarningLimit));
    }
    if (!info->paramHighFailLimit.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << paramHighFailLimit << info->paramHighFailLimit));
    }
    if (!info->paramHighWarningLimit.isEmpty()) {
        parent->addChild(new QTreeWidgetItem(QStringList() << paramHighWarningLimit << info->paramHighWarningLimit));
    }
    parent->addChild(new QTreeWidgetItem(QStringList() << paramModuleIndex << QString::number(info->paramModuleIndex)));

    setColorByStatus(parent->child(7), 1, info->paramStatus);
}

/*************************************************************/

void SnmpResultWidget::setParamList(QTreeWidgetItem *parent, const SnmpParamList *paramList, int modIdx)
{
    foreach(const SnmpParameter &info, *paramList) {
        if (info.paramModuleIndex != modIdx) continue;
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, info.paramDesc);
        item->setText(1, info.paramCurrValue);
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
