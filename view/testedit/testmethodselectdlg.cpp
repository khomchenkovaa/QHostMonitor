#include "testmethodselectdlg.h"

#include <QStandardItem>
#include <QTreeView>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFile>

using namespace SDPO;

/*****************************************************************/

TestMethodSelectDlg::TestMethodSelectDlg(QWidget *parent)
    : QDialog(parent)
    , uiTestMethods     (new QTreeView(this))
    , uiTestDescription (new QTextEdit(this))
    , uiButtonBox       (new QDialogButtonBox(this))
{
    setupUI();
}

/*****************************************************************/

void TestMethodSelectDlg::setCurrent(const int methodId)
{
    if (methodId == -1) return;
    TestMethodMetaInfo method = TestMethod::metaInfo.at(methodId);
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(uiTestMethods->model());
    QList<QStandardItem *> items = model->findItems(method.text, Qt::MatchFixedString | Qt::MatchRecursive);

    if (items.isEmpty()) {
        uiTestMethods->setCurrentIndex(model->index(0,0)); // Ping
    } else {
        QModelIndex idx = model->indexFromItem(items.at(0));
        uiTestMethods->setCurrentIndex(idx);
    }
}

/*****************************************************************/

int TestMethodSelectDlg::getCurrent() const
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(uiTestMethods->model());
    QStandardItem *item = model->itemFromIndex(uiTestMethods->currentIndex());
    int idx = item->data().toInt();
    if (idx > 1000) idx = 0; // Ping
    return idx;
}

/*****************************************************************/

void TestMethodSelectDlg::onTreeTestMethodsChanged()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(uiTestMethods->model());
    QStandardItem *item = model->itemFromIndex(uiTestMethods->currentIndex());
    int idx = item->data().toInt();
    bool okDisabled = false;
    uiTestDescription->clear();
    if (idx > 1000) { //group
        TestGroup group = TestMethod::groups.at(idx-1000);
        uiTestDescription->setPlainText(group.getDescription());
        okDisabled = true;
    } else { // method
        TestMethodMetaInfo method = TestMethod::metaInfo.at(idx);
        if (method.html.isEmpty()) {
            uiTestDescription->setPlainText(method.getDescription());
        } else {
            QFile file(method.html);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                uiTestDescription->setHtml(file.readAll());
                file.close();
            } else {
                uiTestDescription->setPlainText(QString("Cannot open resource file '%1'").arg(method.html));
            }
        }
        uiButtonBox->setDisabled(false);
    }
    uiButtonBox->button(QDialogButtonBox::Ok)->setDisabled(okDisabled);
}

/*****************************************************************/

void TestMethodSelectDlg::setupUI()
{
    if (objectName().isEmpty()) {
        setObjectName(QStringLiteral("TestMethodSelectDlg"));
    }
    resize(700, 450);
    setWindowTitle(tr("Select test method"));
    setWindowIcon(QIcon(":/img/hostMonitor.png"));
    setFont(QFont("DejaVu Sans", 8));

    uiTestMethods->setEditTriggers(QAbstractItemView::NoEditTriggers);
    uiTestMethods->setIconSize(QSize(16, 16));
    uiTestMethods->setHeaderHidden(true);

    uiTestDescription->setReadOnly(true);

    uiButtonBox->setOrientation(Qt::Horizontal);
    uiButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(uiTestMethods);
    splitter->addWidget(uiTestDescription);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(splitter);
    mainLayout->addWidget(uiButtonBox);

    createStandardItemModel();

    connect(uiTestMethods->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &TestMethodSelectDlg::onTreeTestMethodsChanged);
    connect(uiButtonBox, &QDialogButtonBox::accepted,
            this, &QDialog::accept);
    connect(uiButtonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
}

/*****************************************************************/

void TestMethodSelectDlg::createStandardItemModel()
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

    uiTestMethods->setModel(model);
}

/*****************************************************************/

QStandardItem *TestMethodSelectDlg::createItem(const TMethodID methodId)
{
    TestMethodMetaInfo method = TestMethod::metaInfoItem(methodId);
    QStandardItem *item = new QStandardItem(QIcon(method.icon), method.text);
    item->setData(static_cast<int>(method.id));
    return item;
}

/*****************************************************************/

QStandardItem *TestMethodSelectDlg::createGroupItem(const int groupId)
{
    TestGroup group = TestMethod::groups.at(groupId);
    QStandardItem *item = new QStandardItem(QIcon(group.icon), group.name);
    item->setData(groupId + 1000); // groupMarker (or childCount)?
    return item;
}

/*****************************************************************/
