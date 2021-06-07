#include "qMethodSelectDlg.h"
#include "ui_qMethodSelectDlg.h"
#include <QtWidgets>

namespace SDPO {

/*****************************************************************/

MethodSelectDlg::MethodSelectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MethodSelectDlg)
{
    ui->setupUi(this);
    createStandardItemModel();
    connect(ui->treeTestMethods->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(onTreeTestMethodsChanged()));
}

/*****************************************************************/

MethodSelectDlg::~MethodSelectDlg()
{
    delete ui;
}

/*****************************************************************/

void MethodSelectDlg::setCurrent(const int methodId)
{
    TestMethodMetaInfo method = TestMethod::metaInfo.at(methodId);
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->treeTestMethods->model());
    QList<QStandardItem *> items = model->findItems(method.text, Qt::MatchFixedString | Qt::MatchRecursive);

    if (items.isEmpty()) {
        ui->treeTestMethods->setCurrentIndex(model->index(0,0)); // Ping
    } else {
        QModelIndex idx = model->indexFromItem(items.at(0));
        ui->treeTestMethods->setCurrentIndex(idx);
    }
}

/*****************************************************************/

int MethodSelectDlg::getCurrent() const
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->treeTestMethods->model());
    QStandardItem *item = model->itemFromIndex(ui->treeTestMethods->currentIndex());
    int idx = item->data().toInt();
    if (idx > 1000) idx = 0; // Ping
    return idx;
}

/*****************************************************************/

void MethodSelectDlg::onTreeTestMethodsChanged()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->treeTestMethods->model());
    QStandardItem *item = model->itemFromIndex(ui->treeTestMethods->currentIndex());
    int idx = item->data().toInt();
    QStringList description;
    bool okDisabled = false;
    if (idx > 1000) { //group
        TestGroup group = TestMethod::groups.at(idx-1000);
        description = group.description;
        okDisabled = true;
    } else { // method
        TestMethodMetaInfo method = TestMethod::metaInfo.at(idx);
        description = method.description;
        ui->buttonBox->setDisabled(false);
    }
    ui->textDescription->clear();
    foreach(const QString &text, description) {
        ui->textDescription->appendPlainText(text);
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(okDisabled);
}

/*****************************************************************/

void MethodSelectDlg::createStandardItemModel()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    QStandardItem *root = model->invisibleRootItem();
    root->appendRow(createItem(TMethodID::Ping));
    root->appendRow(createItem(TMethodID::TCP));
    root->appendRow(createItem(TMethodID::UDP));
    root->appendRow(createItem(TMethodID::URL));

    QStandardItem *internet = createGroupItem(1);
    internet->appendRow(createItem(TMethodID::NTP));
    internet->appendRow(createItem(TMethodID::SMTP));
    internet->appendRow(createItem(TMethodID::POP3));
    internet->appendRow(createItem(TMethodID::IMAP));
    internet->appendRow(createItem(TMethodID::DNS));
    internet->appendRow(createItem(TMethodID::Ldap));
    internet->appendRow(createItem(TMethodID::Radius));
    internet->appendRow(createItem(TMethodID::HTTP));
    internet->appendRow(createItem(TMethodID::DICOM));
    internet->appendRow(createItem(TMethodID::DHCP));
    root->appendRow(internet);
    root->appendRow(createItem(TMethodID::MailRelay));
    root->appendRow(createItem(TMethodID::Trace));
    root->appendRow(createItem(TMethodID::RAS));

    QStandardItem *disk = createGroupItem(2);
    disk->appendRow(createItem(TMethodID::UNC));
    disk->appendRow(createItem(TMethodID::DriveSpace));
    disk->appendRow(createItem(TMethodID::FileSize));
    disk->appendRow(createItem(TMethodID::CountFiles));
    disk->appendRow(createItem(TMethodID::FileExists));
    disk->appendRow(createItem(TMethodID::FileContents));
    disk->appendRow(createItem(TMethodID::TextLog));
    disk->appendRow(createItem(TMethodID::FileCompare));
    root->appendRow(disk);
    root->appendRow(createItem(TMethodID::Process));
    root->appendRow(createItem(TMethodID::Service));
    root->appendRow(createItem(TMethodID::NTLog));
    root->appendRow(createItem(TMethodID::CPU));
    root->appendRow(createItem(TMethodID::PerfCounter));
    root->appendRow(createItem(TMethodID::WMI));
    root->appendRow(createItem(TMethodID::DominantProcess));

    QStandardItem *snmp = createGroupItem(3);
    snmp->appendRow(createItem(TMethodID::SNMP));
    snmp->appendRow(createItem(TMethodID::SNMPtrap));
    snmp->appendRow(createItem(TMethodID::TrafficMonitor));
    root->appendRow(snmp);

    QStandardItem *db = createGroupItem(4);
    db->appendRow(createItem(TMethodID::ODBC));
    db->appendRow(createItem(TMethodID::Interbase));
    db->appendRow(createItem(TMethodID::MSSQL));
    db->appendRow(createItem(TMethodID::MySQL));
    db->appendRow(createItem(TMethodID::Oracle));
    db->appendRow(createItem(TMethodID::Postgre));
    db->appendRow(createItem(TMethodID::Sybase));
    root->appendRow(db);

    QStandardItem *external = createGroupItem(5);
    external->appendRow(createItem(TMethodID::Script));
    external->appendRow(createItem(TMethodID::ShellScript));
    external->appendRow(createItem(TMethodID::Externalprg));
    external->appendRow(createItem(TMethodID::SSH));
    root->appendRow(external);
    root->appendRow(createItem(TMethodID::TempMonitor));
    root->appendRow(createItem(TMethodID::HMmonitor));

    ui->treeTestMethods->setModel(model);
}

/*****************************************************************/

QStandardItem *MethodSelectDlg::createItem(const TMethodID methodId)
{
    TestMethodMetaInfo method = TestMethod::metaInfoItem(methodId);
    QStandardItem *item = new QStandardItem(QIcon(method.icon), method.text);
    item->setData(static_cast<int>(method.id));
    return item;
}

/*****************************************************************/

QStandardItem *MethodSelectDlg::createGroupItem(const int groupId)
{
    TestGroup group = TestMethod::groups.at(groupId);
    QStandardItem *item = new QStandardItem(QIcon(group.icon), group.name);
    item->setData(groupId + 1000); // groupMarker (or childCount)?
    return item;
}

/*****************************************************************/

} // namespace SDPO
