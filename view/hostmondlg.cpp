#include "hostmondlg.h"
#include "ui_hostmondlg.h"

#include "qAlertsEditWidget.h"
#include "qLogReportsEditWidget.h"
#include "qMasterTestsEditWidget.h"
#include "qExpressionTestsEditWidget.h"
#include "qLinksList.h"
#include "qMacroEditorDlg.h"
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
    ui->treeDependentTests->clear();

    // Optional
    ui->chkReverseAlert->setChecked(false);
    ui->chkUnknownIsBad->setChecked(true);
    ui->chkWarningIsBad->setChecked(true);
    ui->chkUseWarningIf->setChecked(false);
    ui->chkUseNormalIf->setChecked(false);
    ui->chkTuneUpReply->setChecked(false);
    ui->cmbWarningCondition->setCurrentText(QString());
    ui->cmbNormalCondition->setCurrentText(QString());
    ui->cmbReply->setCurrentText(QString());
    ui->cmbEnabled->setCurrentIndex(0);
    ui->btnLinks->setVisible(false);
}

/******************************************************************/

void HostMonDlg::hideDependencies(bool hide)
{
    ui->btnDependenciesHideLeft->setChecked(hide);
    ui->btnDependenciesHideRight->setChecked(hide);
    if (ui->frmMasterTests->isHidden() != hide) {
        ui->frmMasterTests->setHidden(hide);
        ui->frmDependentTests->setHidden(hide);
        QSize newSize = size();
        int h = newSize.height();
        newSize.setHeight( hide ? h - ui->frmMasterTests->height() : h + ui->frmMasterTests->height() );
        qDebug() << "Size changed from:" << h << "to" << newSize.height();
        resize(newSize);
    }
}

/******************************************************************/

void HostMonDlg::hideOptional(bool hide)
{
    if (ui->frmOptional->isHidden() == hide) {
        return;
    }
    ui->btnStatusProcessingHide->setChecked(hide);
    ui->frmOptional->setHidden(hide);
    QSize newSize = size();
    int h = newSize.height();
    newSize.setHeight( hide ? h - ui->frmOptional->height() : h + ui->frmOptional->height() );
    qDebug() << "Size changed from:" << h << "to" << newSize.height();
    resize(newSize);
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

    // optional
    m_Item->setReverseAlert(ui->chkReverseAlert->isChecked());
    m_Item->setUnknownIsBad(ui->chkUnknownIsBad->isChecked());
    m_Item->setWarningIsBad(ui->chkWarningIsBad->isChecked());
    m_Item->setUseWarningScript(ui->chkUseWarningIf->isChecked());
    m_Item->setUseNormalScript(ui->chkUseNormalIf->isChecked());
    m_Item->setTuneUpReply(ui->chkTuneUpReply->isChecked());
    m_Item->setWarningScript(ui->cmbWarningCondition->currentText());
    m_Item->setNormalScript(ui->cmbNormalCondition->currentText());
    m_Item->setTuneUpScript(ui->cmbReply->currentText());
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
    ui->treeDependentTests->clear();
    //! TODO implement DependentTests init

    // optional
    ui->cmbEnabled->setCurrentIndex(m_Item->isEnabled()?0:1);
    ui->chkReverseAlert->setChecked(m_Item->isReverseAlert());
    ui->chkUnknownIsBad->setChecked(m_Item->isUnknownIsBad());
    ui->chkWarningIsBad->setChecked(m_Item->isWarningIsBad());
    ui->chkUseWarningIf->setChecked(m_Item->isUseWarningScript());
    ui->chkUseNormalIf->setChecked(m_Item->isUseNormalScript());
    ui->chkTuneUpReply->setChecked(m_Item->isTuneUpReply());
    ui->cmbWarningCondition->setCurrentText(m_Item->getWarningScript());
    ui->cmbNormalCondition->setCurrentText(m_Item->getNormalScript());
    ui->cmbReply->setCurrentText(m_Item->getTuneUpScript());
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

void HostMonDlg::on_btnWarningCondition_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Use 'Warning' status if"));
    dlg.setScript(ui->cmbWarningCondition->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbWarningCondition->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void HostMonDlg::on_btnNormalCondition_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Use 'Normal' status if"));
    dlg.setScript(ui->cmbNormalCondition->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbNormalCondition->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void HostMonDlg::on_btnTuneUpReply_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Tune up reply"));
    dlg.setScript(ui->cmbReply->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbReply->setCurrentText(dlg.getScript());
    }
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
    connect(ui->btnDependenciesHideRight, &QPushButton::toggled,
            this, &HostMonDlg::hideDependencies);
    connect(ui->btnStatusProcessingHide, &QPushButton::toggled,
            this, &HostMonDlg::hideOptional);
    connect(ui->cmbDependencyMode, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->stwMasterTest, &QStackedWidget::setCurrentIndex);
    connect(ui->chkSynchronizeCounters, &QCheckBox::toggled,
            ui->chkSynchronizeStatusAlerts, &QCheckBox::setEnabled);
    connect(ui->btnCancel, &QPushButton::clicked,
            this, &HostMonDlg::close);

}


/******************************************************************/

} // namespace SDPO
