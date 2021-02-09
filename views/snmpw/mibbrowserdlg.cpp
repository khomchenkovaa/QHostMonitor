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
    sizePolicy.setHeightForWidth(false);
    mibBrowserWidget->setSizePolicy(sizePolicy);

    QDialogButtonBox *btnBox = new QDialogButtonBox(this);
    btnBox->setOrientation(Qt::Horizontal);
    btnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    QToolButton *btnGetValue = new QToolButton(this);
    btnGetValue->setDefaultAction(mibBrowserWidget->actionGetValue());
    btnGetValue->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btnGetValue->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    QToolButton *btnGetTable = new QToolButton(this);
    btnGetTable->setDefaultAction(mibBrowserWidget->actionGetTable());
    btnGetTable->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btnGetTable->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    QToolButton *btnFindName = new QToolButton(this);
    btnFindName->setDefaultAction(mibBrowserWidget->actionFindName());
    btnFindName->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btnFindName->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    QToolButton *btnFindOid = new QToolButton(this);
    btnFindOid->setDefaultAction(mibBrowserWidget->actionFindOid());
    btnFindOid->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btnFindOid->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(btnGetValue);
    horizontalLayout->addWidget(btnGetTable);
    horizontalLayout->addWidget(btnFindName);
    horizontalLayout->addWidget(btnFindOid);
    horizontalLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    horizontalLayout->addWidget(btnBox);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mibBrowserWidget);
    mainLayout->addLayout(horizontalLayout);

    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

/******************************************************************/
