#include "snmpresultlog.h"

#include <QTreeWidget>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QHeaderView>

using namespace KharmonView;

/*************************************************************/

SnmpResultLog::SnmpResultLog(SnmpObject *node, QWidget *parent)
    : QDialog(parent)
    , uiMessages(new QTreeWidget(this))
{
    setupUI();
    init(node);
}

/*************************************************************/

void SnmpResultLog::setupUI()
{
    QFont font;
    font.setPointSize(9);
    setFont(font);
    resize(800, 400);

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    uiMessages->setSizePolicy(sizePolicy);

    QString styleSheet =
        "QTreeWidget::item:!selected { "
        "border: 1px solid gainsboro; "
        "border-left: none; "
        "border-top: none; "
        "} "
        "QTreeView::item:selected {}";

    uiMessages->setStyleSheet(styleSheet);
    uiMessages->setAlternatingRowColors(true);
    uiMessages->setIndentation(0);
    uiMessages->setColumnCount(6);
    uiMessages->setMinimumWidth(600);
    uiMessages->setHeaderLabels(QStringList() << "" << "ID" << "Date" << "Type" << "Priority" << "Message");
    uiMessages->setFont(font);
    uiMessages->header()->setFont(font);

//    QDialogButtonBox *uiButtonBox = new QDialogButtonBox(this);
//    uiButtonBox->setOrientation(Qt::Vertical);
//    uiButtonBox->setStandardButtons(QDialogButtonBox::Close);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(uiMessages);
//    mainLayout->addWidget(uiButtonBox);

//    connect(uiButtonBox, &QDialogButtonBox::rejected, this, &QDialog::accept);
//    connect(uiButtonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

/*************************************************************/

void SnmpResultLog::init(SnmpObject *node)
{
    if (node == Q_NULLPTR) return;
    setWindowTitle(tr("Log Messages for %1").arg(node->getName()));

    SnmpLogList *logList = node->snmpLogList();
    foreach(const SnmpLog &info, *logList) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setIcon(0, iconByPriority(info.logPriority));
        item->setText(1, QString::number(info.logID));
        item->setText(2, info.logDate);
        item->setText(3, QString::number(info.logType));
        item->setText(4, logPriority(info.logPriority));
        item->setText(5, info.logMessage);
        setColorByPriority(item, info.logPriority);
        uiMessages->addTopLevelItem(item);
    }
    for (int i=0; i< uiMessages->columnCount(); ++i) {
        uiMessages->resizeColumnToContents(i);
    }
}

/*************************************************************/

QString SnmpResultLog::logPriority(int priority)
{
    static const QStringList priorityStr =
            QStringList() << "EMERG" << "ALERT" << "CRIT" << "ERR" << "WARN" << "NOTICE" << "INFO" << "DEBUG";
    return priorityStr.at(priority);
}

/*************************************************************/

void SnmpResultLog::setColorByPriority(QTreeWidgetItem *item, int priority)
{
    QBrush brush = item->foreground(4);
    switch (priority) {
    case 0: // "EMERG"
    case 1: // "ALERT"
    case 2: // "CRIT"
    case 3: // "ERR"
        brush.setColor(Qt::darkRed);
        break;
    case 4: // "WARN"
        brush.setColor(Qt::darkBlue);
        break;
    case 6: // "INFO"
        brush.setColor(Qt::darkGreen);
        break;
    }
    item->setForeground(4, brush);
}

/*************************************************************/

QIcon SnmpResultLog::iconByPriority(int priority)
{
    switch (priority) {
    case 0: // "EMERG"
    case 1: // "ALERT"
    case 2: // "CRIT"
    case 3: // "ERR"
        return QIcon::fromTheme(QStringLiteral("dialog-error"));
    case 4: // "WARN"
        return QIcon::fromTheme(QStringLiteral("dialog-warning"));
    }
    return QIcon::fromTheme(QStringLiteral("dialog-information"));
}

/*************************************************************/
