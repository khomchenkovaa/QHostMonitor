#include "hostmondlg.h"
#include "ui_hostmondlg.h"

#include "qAlertsEditWidget.h"
#include "qLogReportsEditWidget.h"
#include "qMasterTestsEditWidget.h"
#include "qExpressionTestsEditWidget.h"
#include "qLinksList.h"
#include "settings.h"
#include "tTest.h"
#include "tRoot.h"
#include "hmListService.h"

#include <QtWidgets>
#include <QDebug>

namespace SDPO {

/******************************************************************/

HostMonDlg::HostMonDlg(HMListService *hml, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HostMonDlg)
    , m_HML(hml)
    , m_Item(nullptr)
    , changed(false)
{
    ui->setupUi(this);
    setupUI();
}

/******************************************************************/

HostMonDlg::~HostMonDlg()
{
    delete ui;
}

/******************************************************************/

void HostMonDlg::on_btnOk_clicked()
{
    if (saveTest()) {
        close();
    }
}

/******************************************************************/

void HostMonDlg::reset()
{
    //main
    ui->frmTest->reset();

    // Schedule
    ui->frmSchedule->reset();

    // Alerts
    AlertsEditWidget *alerts = qobject_cast<AlertsEditWidget*>(ui->grpAlerts);
    if (alerts) {
        alerts->reset();
    }

    // Log & reports
    LogReportsEditWidget *logReports = qobject_cast<LogReportsEditWidget*>(ui->grpLogsReports);
    if (logReports) {
        logReports->reset();
    }

    // Master tests
    ui->cmbDependencyMode->setCurrentIndex(0);
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->reset(m_HML->rootFolder());
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->reset();
    }
    ui->chkSynchronizeCounters->setChecked(true);
    ui->chkSynchronizeStatusAlerts->setChecked(false);

    // Dependencies
    ui->grpDependencies->reset();

    // Optional
    ui->frmOptional->reset();

    ui->cmbEnabled->setCurrentIndex(0);
    ui->btnLinks->setVisible(false);
}

/******************************************************************/

void HostMonDlg::hideDependencies(bool hide)
{
    int hRight = ui->grpDependencies->doHide(hide);
    int hLeft = 0;
    ui->btnDependenciesHideLeft->setChecked(hide);
    if (ui->frmMasterTests->isHidden() != hide) {
        if (hide) {
            hLeft = ui->frmMasterTests->height();
        }
        ui->frmMasterTests->setHidden(hide);
    }

    int delta = qMax(hRight, hLeft);
    if (delta) {
        QSize newSize = size();
        int h = newSize.height();
        newSize.setHeight(h - delta);
        resize(newSize);
    }
}

/******************************************************************/

bool HostMonDlg::saveTest()
{
    bool isNew = (m_Item == nullptr);
    TTest *test = ui->frmTest->save(m_HML, m_Item);
    if (test == nullptr) return false;
    m_Item = test;
    // schedule
    ui->frmSchedule->save(m_Item);

    // alerts
    AlertsEditWidget *alerts = qobject_cast<AlertsEditWidget*>(ui->grpAlerts);
    if (alerts) {
        alerts->save(m_Item);
    }

    // Log & reports
    LogReportsEditWidget *logReports = qobject_cast<LogReportsEditWidget*>(ui->grpLogsReports);
    if (logReports) {
        logReports->save(m_Item);
    }

    // Master tests
    m_Item->setDependencyMode(ui->cmbDependencyMode->currentIndex());
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->save(m_Item);
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->save(m_Item);
    }
    m_Item->setSynchronizeCounters(ui->chkSynchronizeCounters->isChecked());
    m_Item->setSynchronizeStatusAlerts(ui->chkSynchronizeStatusAlerts->isChecked());

    ui->grpDependencies->save(m_Item);

    // optional
    ui->frmOptional->save(m_Item);

    m_Item->setEnabled(ui->cmbEnabled->currentIndex() == 0);

    if (isNew) {
        m_HML->addNode(m_HML->currentFolder(),m_Item);
        // emit testAdded(m_Item);
    } else {
        emit testChanged(m_Item);
    }
    return true;
}

/******************************************************************/

void HostMonDlg::init(TTest *item)
{
    m_Item = item;
    if(!m_Item) {
        init(TMethodID::Ping);
        return;
    }
    // main
    ui->frmTest->init(item);

    // schedule


    // alerts
    AlertsEditWidget *alerts = qobject_cast<AlertsEditWidget*>(ui->grpAlerts);
    if (alerts) {
        alerts->init(m_Item);
    }

    // Log & reports
    LogReportsEditWidget *logReports = qobject_cast<LogReportsEditWidget*>(ui->grpLogsReports);
    if (logReports) {
        logReports->init(m_Item);
    }

    // Master tests
    ui->cmbDependencyMode->setCurrentIndex(m_Item->getDependencyMode());
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->init(m_Item);
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->init(m_Item);
    }
    ui->chkSynchronizeCounters->setChecked(m_Item->isSynchronizeCounters());
    ui->chkSynchronizeStatusAlerts->setChecked(m_Item->isSynchronizeStatusAlerts());

    ui->grpDependencies->init(m_Item);

    // optional
    ui->frmOptional->init(m_Item);

    ui->cmbEnabled->setCurrentIndex(m_Item->isEnabled()?0:1);
    ui->btnLinks->setVisible(m_Item->linkCount() > 0);
}

/******************************************************************/

void HostMonDlg::init(TMethodID method, QVariant data)
{
    m_Item = nullptr;
    ui->frmTest->setData(data);
    reset();
    ui->frmTest->setMethodID(method);
}

/******************************************************************/

void HostMonDlg::on_btnLinks_clicked()
{
    if (!m_Item) return;
    if (m_Item->linkCount() == 0) return;

    LinksList linksDlg(m_Item);
    linksDlg.setReadOnly();
    linksDlg.exec();
}

/******************************************************************/

void HostMonDlg::setupUI()
{
    if (objectName().isEmpty()) {
        setObjectName(QStringLiteral("HostMonDlg"));
    }
    resize(921, 693);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);

    setFont(QFont("DejaVu Sans", 8));

    setWindowIcon(QIcon(":/img/hostMonitor.png"));
    setWindowTitle(QApplication::translate("HostMonDlg", "Test properties", Q_NULLPTR));
    setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

    // TODO migrate from ui_qHostMonDlg.h

    connect(ui->btnDependenciesHideLeft, &QPushButton::toggled,
            this, &HostMonDlg::hideDependencies);
    connect(ui->grpDependencies, &DependenciesEditWidget::hideMe,
            this, &HostMonDlg::hideDependencies);
    connect(ui->cmbDependencyMode, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->stwMasterTest, &QStackedWidget::setCurrentIndex);
    connect(ui->chkSynchronizeCounters, &QCheckBox::toggled,
            ui->chkSynchronizeStatusAlerts, &QCheckBox::setEnabled);
    connect(ui->btnCancel, &QPushButton::clicked,
            this, &HostMonDlg::close);

}


/******************************************************************/

} // namespace SDPO
