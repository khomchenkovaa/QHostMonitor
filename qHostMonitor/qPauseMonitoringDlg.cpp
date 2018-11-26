#include "qPauseMonitoringDlg.h"
#include "ui_qPauseMonitoringDlg.h"
#include "monitoringService.h"
#include "actionService.h"
#include "gData.h"
#include "qActionProfiles.h"
#include "io/ioActionProfileLoader.h"

namespace SDPO {

/******************************************************************/

PauseMonitoringDlg::PauseMonitoringDlg(MonitoringService * monitoring, ActionService * alerts, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseMonitoringDlg),
    m_MonitoringService(monitoring),
    m_ActionService(alerts)
{
    ui->setupUi(this);

    reset();
    loadMonitoringData();
    loadAlertsData();
}

/******************************************************************/

PauseMonitoringDlg::~PauseMonitoringDlg()
{
    delete ui;
}

/******************************************************************/

void PauseMonitoringDlg::on_btnMonitoringStarted_clicked()
{
    btnActionsClick(ui->cmbMonitoringStarted);
}

/******************************************************************/

void PauseMonitoringDlg::on_btnMonitoringStopped_clicked()
{
    btnActionsClick(ui->cmbMonitoringStopped);
}

/******************************************************************/

void PauseMonitoringDlg::on_btnAlertingStarted_clicked()
{
    btnActionsClick(ui->cmbAlertingStarted);
}

/******************************************************************/

void PauseMonitoringDlg::on_btnAlertingStopped_clicked()
{
    btnActionsClick(ui->cmbAlertingStopped);
}

/******************************************************************/

void PauseMonitoringDlg::on_btnBoxPauseMonitoring_accepted()
{
    saveMonitoringData();
    saveAlertsData();
    accept();
}

/******************************************************************/

void PauseMonitoringDlg::reset()
{
    QString monitoringStarted = ui->cmbMonitoringStarted->currentText();
    QString monitoringStopped = ui->cmbMonitoringStopped->currentText();
    QString alertingStarted = ui->cmbAlertingStarted->currentText();
    QString alertingStopped = ui->cmbAlertingStopped->currentText();

    ui->cmbMonitoringStarted->clear();
    ui->cmbMonitoringStopped->clear();
    ui->cmbAlertingStarted->clear();
    ui->cmbAlertingStopped->clear();
    foreach(const GActionProfile &profile, GData::actionProfiles) {
        ui->cmbMonitoringStarted->addItem(profile.name);
        ui->cmbMonitoringStopped->addItem(profile.name);
        ui->cmbAlertingStarted->addItem(profile.name);
        ui->cmbAlertingStopped->addItem(profile.name);
    }

    ui->cmbMonitoringStarted->setCurrentText(monitoringStarted);
    ui->cmbMonitoringStopped->setCurrentText(monitoringStopped);
    ui->cmbAlertingStarted->setCurrentText(alertingStarted);
    ui->cmbAlertingStopped->setCurrentText(alertingStopped);
}

/******************************************************************/

void PauseMonitoringDlg::loadMonitoringData()
{
    ui->chkMonitoringPause->setChecked(m_MonitoringService->isPaused());
    ui->dateMonitoringPause->setDate(m_MonitoringService->pausedTil().date());
    ui->timeMonitoringPause->setTime(m_MonitoringService->pausedTil().time());
    ui->chkMonitoringStarted->setChecked(m_MonitoringService->isUseStartAction());
    ui->cmbMonitoringStarted->setCurrentText(m_MonitoringService->getStartAction());
    ui->chkMonitoringStopped->setChecked(m_MonitoringService->isUseStopAction());
    ui->cmbMonitoringStopped->setCurrentText(m_MonitoringService->getStopAction());
}

/******************************************************************/

void PauseMonitoringDlg::loadAlertsData()
{
    ui->chkAlertingPause->setChecked(m_ActionService->isPaused());
    ui->dateAlertingPause->setDate(m_ActionService->pausedTil().date());
    ui->timeAlertingPause->setTime(m_ActionService->pausedTil().time());
    ui->chkAlertingStarted->setChecked(m_ActionService->isUseStartAction());
    ui->cmbAlertingStarted->setCurrentText(m_ActionService->getStartAction());
    ui->chkAlertingStopped->setChecked(m_ActionService->isUseStopAction());
    ui->cmbAlertingStopped->setCurrentText(m_ActionService->getStopAction());
}

/******************************************************************/

void PauseMonitoringDlg::saveMonitoringData()
{
    QDateTime dt = QDateTime::currentDateTime();
    dt.setDate(ui->dateMonitoringPause->date());
    dt.setTime(ui->timeMonitoringPause->time());
    m_MonitoringService->setPaused(ui->chkMonitoringPause->isChecked(), dt);
    m_MonitoringService->setUseStartAction(ui->chkMonitoringStarted->isChecked(), ui->cmbMonitoringStarted->currentText());
    m_MonitoringService->setUseStopAction(ui->chkMonitoringStopped->isChecked(), ui->cmbMonitoringStopped->currentText());
}

/******************************************************************/

void PauseMonitoringDlg::saveAlertsData()
{
    QDateTime dt = QDateTime::currentDateTime();
    dt.setDate(ui->dateAlertingPause->date());
    dt.setTime(ui->timeAlertingPause->time());
    m_ActionService->setPaused(ui->chkAlertingPause->isChecked(), dt);
    m_ActionService->setUseStartAction(ui->chkAlertingStarted->isChecked(), ui->cmbAlertingStarted->currentText());
    m_ActionService->setUseStopAction(ui->chkAlertingStopped->isChecked(), ui->cmbAlertingStopped->currentText());
}

/******************************************************************/

void PauseMonitoringDlg::btnActionsClick(QComboBox *cmb)
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(cmb->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset();
        cmb->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

} // namespace SDPO
