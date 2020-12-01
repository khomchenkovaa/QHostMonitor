#include "mibbrowserdlg.h"
#include "mibbrowserwidget.h"
#include "qMibGetValueDlg.h"
#include "qMibGetTableDlg.h"

#include <QtWidgets>

using namespace SDPO;

/******************************************************************/

MibBrowserDlg::MibBrowserDlg(QWidget *parent) :
    QDialog(parent),
    mibBrowserWidget(new MibBrowserWidget(this))
{
    setupUI();
}

/******************************************************************/

MibBrowserDlg::~MibBrowserDlg()
{
}

/******************************************************************/

QString MibBrowserDlg::getOid() const
{
    return mibBrowserWidget->getOid();
}

/******************************************************************/

void MibBrowserDlg::setOid(const QString oid)
{
    mibBrowserWidget->setOid(oid);
}

/******************************************************************/

void MibBrowserDlg::openGetValueDlg()
{
    QMibGetValueDlg dlg;
    dlg.setOid(mibBrowserWidget->getOid());
    dlg.exec();
}

/******************************************************************/

void MibBrowserDlg::openGetTableDlg()
{
    QMibGetTableDlg dlg;
    dlg.setOid(mibBrowserWidget->getOid());
    dlg.exec();
}

/******************************************************************/

void MibBrowserDlg::openFindNameDlg()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Find Name"),tr("Name (e.g. sysUptime)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        mibBrowserWidget->findByName(name);
    }
}

/******************************************************************/

void MibBrowserDlg::openFindOidDlg()
{
    bool ok;
    QString oid = QInputDialog::getText(this, tr("Find OID"),tr("OID (e.g. 1.3.6.1.2.1.1.1)"), QLineEdit::Normal, QString(), &ok);
    if (ok) {
        mibBrowserWidget->setOid(oid);
    }
}

/******************************************************************/

void MibBrowserDlg::setupUI()
{
    QFont font;
    font.setPointSize(9);
    setFont(font);

    setWindowIcon(QIcon(":/img/hostMonitor.png"));

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mibBrowserWidget->sizePolicy().hasHeightForWidth());
    mibBrowserWidget->setSizePolicy(sizePolicy);

    QDialogButtonBox *btnBox = new QDialogButtonBox(this);
    btnBox->setOrientation(Qt::Vertical);
    btnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    QPushButton *btnGetValue = new QPushButton(QIcon(":/img/test/snmp_get.png"), "Get Value", this);
    QPushButton *btnGetTable = new QPushButton(QIcon(":/img/test/snmp_table.png"), "Get Table", this);
    QPushButton *btnFindName = new QPushButton(QIcon(":/img/test/find.png"), "Find Name", this);
    QPushButton *btnFindOid  = new QPushButton(QIcon(":/img/test/find.png"), "Find OID", this);

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(btnBox);
    verticalLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    verticalLayout->addWidget(btnGetValue);
    verticalLayout->addWidget(btnGetTable);
    verticalLayout->addWidget(btnFindName);
    verticalLayout->addWidget(btnFindOid);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(mibBrowserWidget);
    mainLayout->addLayout(verticalLayout);

    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(btnGetValue, &QPushButton::clicked, this, &MibBrowserDlg::openGetValueDlg);
    connect(btnGetTable, &QPushButton::clicked, this, &MibBrowserDlg::openGetTableDlg);
    connect(btnFindName, &QPushButton::clicked, this, &MibBrowserDlg::openFindNameDlg);
    connect(btnFindOid, &QPushButton::clicked, this, &MibBrowserDlg::openFindOidDlg);
}

/******************************************************************/
