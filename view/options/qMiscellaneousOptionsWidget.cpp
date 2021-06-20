#include "qMiscellaneousOptionsWidget.h"
#include "ui_qMiscellaneousOptionsWidget.h"
#include "qActionProfiles.h"
#include "io/ioActionProfileLoader.h"
#include "gData.h"

namespace SDPO {

/******************************************************************/

MiscellaneousOptionsWidget::MiscellaneousOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::MiscellaneousOptionsWidget)
{
    ui->setupUi(this);
    ui->swMisc->setCurrentIndex(0);
}

/******************************************************************/

MiscellaneousOptionsWidget::~MiscellaneousOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void MiscellaneousOptionsWidget::reset_SnmpTrapAction()
{
    ui->cmbSelectActionProfile->clear();
    foreach(const GActionProfile &profile, GData::actionProfiles) {
        ui->cmbSelectActionProfile->addItem(profile.name);
    }
}

/******************************************************************/

void MiscellaneousOptionsWidget::on_btnSelectActionProfile_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbSelectActionProfile->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_SnmpTrapAction();
        ui->cmbSelectActionProfile->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void MiscellaneousOptionsWidget::init(QSettings *s)
{
    // Date & Time format
    ui->chkDateTimeFixed->setChecked(s->value(SKEY_FF_UseFixedFormats, SVAL_FF_UseFixedFormats).toInt());
    on_selectDateFormat();
    connect(ui->chkDateTimeFixed, SIGNAL(clicked()),this, SLOT(on_selectDateFormat()));
    ui->cmbDateFormat->setCurrentIndex(s->value(SKEY_FF_FixedDateFormat, SVAL_FF_FixedDateFormat).toInt());
    ui->cmbTimeFormat->setCurrentIndex(s->value(SKEY_FF_FixedTimeFormat, SVAL_FF_FixedTimeFormat).toInt());

    // Reports & Statistics
    ui->chkShowFolderNames->setChecked(s->value(SKEY_REPORTS_ShowFolders, SVAL_REPORTS_ShowFolders).toInt());
    ui->chkSkipEmptyFolders->setChecked(s->value(SKEY_REPORTS_SkipEmptyFolders, SVAL_REPORTS_SkipEmptyFolders).toInt());
    if (s->value(SKEY_MISC_AliveDeadRatioMode, SVAL_MISC_AliveDeadRatioMode).toInt()) {
        ui->rbDisplayRatioTime->setChecked(true);
    } else {
        ui->rbDisplayRatioTests->setChecked(true);
    }
    ui->spinPrecision->setValue(s->value(SKEY_ENVIRON_DigitsAfterDotStat, SVAL_ENVIRON_DigitsAfterDotStat).toInt());

    // ODBC tests & logging
    ui->chkNotSqlFetch->setChecked(s->value(SKEY_MISC_DoNotUseSqlFetchAbsolute, SVAL_MISC_DoNotUseSqlFetchAbsolute).toInt());
    if(s->value(SKEY_MISC_OdbcUseSystemDsn, SVAL_MISC_OdbcUseSystemDsn).toInt()) {
        ui->rbDsnSystem->setChecked(true);
    } else {
        ui->rbDsnUser->setChecked(true);
    }
    ui->chkEnableConnectionPooling->setChecked(s->value(SKEY_MISC_OdbcConnectionPooling, SVAL_MISC_OdbcConnectionPooling).toInt());

    // RMA / Logging
    if (s->value(SKEY_LOGGING_RecordPrimaryRMAErrors, SVAL_LOGGING_RecordPrimaryRMAErrors).toInt()) {
        ui->rbRequestBackup->setChecked(true);
    } else {
        ui->rbSetUnknown->setChecked(true);
    }
    ui->chkLogAboutInactive->setChecked(s->value(SKEY_LOGGING_LogStateChanges, SVAL_LOGGING_LogStateChanges).toInt());

    // Update check
    if (s->value(SKEY_UPDATE_AutoMode, SVAL_UPDATE_AutoMode).toInt()) {
        ui->rbNoUpdates->setChecked(true);
    } else {
        ui->rbUpdateCheck->setChecked(true);
    }

    // SSL options
    ui->chkAcceptInvalidHostsPop3->setChecked (s->value(SKEY_MISC_sslAnyHostPOP3, SVAL_MISC_sslAnyHostPOP3).toInt());
    ui->chkAcceptInvalidDatesPop3->setChecked (s->value(SKEY_MISC_sslAnyDatePOP3, SVAL_MISC_sslAnyDatePOP3).toInt());
    ui->chkIgnoreAuthorityPop3->setChecked    (s->value(SKEY_MISC_sslAnyAuthPOP3, SVAL_MISC_sslAnyAuthPOP3).toInt());
    ui->chkAcceptInvalidHostsImap->setChecked (s->value(SKEY_MISC_sslAnyHostIMAP, SVAL_MISC_sslAnyHostIMAP).toInt());
    ui->chkAcceptInvalidDatesImap->setChecked (s->value(SKEY_MISC_sslAnyDateIMAP, SVAL_MISC_sslAnyDateIMAP).toInt());
    ui->chkIgnoreAuthorityImap->setChecked    (s->value(SKEY_MISC_sslAnyAuthIMAP, SVAL_MISC_sslAnyAuthIMAP).toInt());
    ui->chkAcceptInvalidHostsLdap->setChecked (s->value(SKEY_MISC_sslAnyHostLDAP, SVAL_MISC_sslAnyHostLDAP).toInt());
    ui->chkAcceptInvalidDatesLdap->setChecked (s->value(SKEY_MISC_sslAnyDateLDAP, SVAL_MISC_sslAnyDateLDAP).toInt());
    ui->chkIgnoreAuthorityLdap->setChecked    (s->value(SKEY_MISC_sslAnyAuthLDAP, SVAL_MISC_sslAnyAuthLDAP).toInt());

    // Settings for URL tests
    ui->chkNotCheckConnection->setChecked (s->value(SKEY_HOSTMON_CheckInternetConnection, SVAL_HOSTMON_CheckInternetConnection).toInt());
    ui->cmbAgentName->setCurrentText      (s->value(SKEY_MISC_DefAgentName, SVAL_MISC_DefAgentName).toString());
    ui->chkAcceptInvalidHosts->setChecked (s->value(SKEY_MISC_IgnoreCertCnInvalid, SVAL_MISC_IgnoreCertCnInvalid).toInt());
    ui->chkAcceptInvalidDates->setChecked (s->value(SKEY_MISC_IgnoreCertDateInvalid, SVAL_MISC_IgnoreCertDateInvalid).toInt());

    // Settings for UNC tests
    ui->spinUncRetries->setValue(s->value(SKEY_MISC_UncRetries, SVAL_MISC_UncRetries).toInt());
    switch (s->value(SKEY_MISC_UncMode, SVAL_MISC_UncMode).toInt()) {
    case 1: ui->rbUncOnePerServer->setChecked(true); break;
    case 2: ui->rbUncOneByOne->setChecked(true); break;
    default: // case 0:
        ui->rbUncNormal->setChecked(true); break;
    }
    ui->chkErrorInReply->setChecked(s->value(SKEY_MISC_UncShowErrors, SVAL_MISC_UncShowErrors).toInt());

    // NT event log tests
    ui->chkShowEventsDecription->setChecked(s->value(SKEY_MISC_ShowNTEventDescr, SVAL_MISC_ShowNTEventDescr).toInt());

    // Performance counter
    switch(s->value(SKEY_MISC_PerfWorkMode, SVAL_MISC_PerfWorkMode).toInt()) {
    case 1: ui->rbModeOneByOne->setChecked(true); break;
    case 2: ui->rbModeSmart->setChecked(true); break;
    case 3: ui->rbModeExternal->setChecked(true); break;
    default: // case 0:
        ui->rbModeMultiThread->setChecked(true); break;
    }

    // SNMP Get tests
    ui->chkSnmpAppend0->setChecked(s->value(SKEY_MISC_SnmpAutoSingleInstance, SVAL_MISC_SnmpAutoSingleInstance).toInt());

    // SNMP Trap tests
    reset_SnmpTrapAction();
    ui->spinSnmpTrapUdpPort->setValue          (s->value(SKEY_TRAP_Port, SVAL_TRAP_Port).toInt());
    ui->grpSnmpTrafficAlert->setChecked        (s->value(SKEY_TRAP_TrafficCheck, SVAL_TRAP_TrafficCheck).toInt());
    ui->spinSnmpAlertMessages->setValue        (s->value(SKEY_TRAP_TrafficLimit, SVAL_TRAP_TrafficLimit).toInt());
    ui->spinSnmpAlertSeconds->setValue         (s->value(SKEY_TRAP_TrafficSpan, SVAL_TRAP_TrafficSpan).toInt());
    ui->chkSnmpSuspend->setChecked             (s->value(SKEY_TRAP_Pause, SVAL_TRAP_Pause).toInt());
    ui->spinSnmpSuspendTime->setValue          (s->value(SKEY_TRAP_PauseSpan, SVAL_TRAP_PauseSpan).toInt());
    ui->chkExecuteAtionProfile->setChecked     (s->value(SKEY_TRAP_Action, SVAL_TRAP_Action).toInt());
    ui->cmbSelectActionProfile->setCurrentIndex(s->value(SKEY_TRAP_ActionID, SVAL_TRAP_ActionID).toInt());

    // Traffic monitor tests
    switch (s->value(SKEY_MISC_TrafficMonitorUnits, SVAL_MISC_TrafficMonitorUnits).toInt()) {
    case 1: ui->rbTrafficInKbit->setChecked(true); break;
    case 2: ui->rbTestSettings->setChecked(true); break;
    default: // case 0:
        ui->rbTrafficInKB->setChecked(true); break;
    }
}

/******************************************************************/

void MiscellaneousOptionsWidget::prepareToSave(QSettings *s)
{      
    // Date & Time format
    s->setValue(SKEY_FF_UseFixedFormats, ui->chkDateTimeFixed->isChecked()?1:0);
    s->setValue(SKEY_FF_FixedDateFormat, ui->cmbDateFormat->currentIndex());
    s->setValue(SKEY_FF_FixedTimeFormat, ui->cmbTimeFormat->currentIndex());

    // Reports & Statistics
    s->setValue(SKEY_REPORTS_ShowFolders, ui->chkShowFolderNames->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_SkipEmptyFolders, ui->chkSkipEmptyFolders->isChecked()?1:0);
    s->setValue(SKEY_MISC_AliveDeadRatioMode, ui->rbDisplayRatioTime->isChecked()?1:0);
    s->setValue(SKEY_ENVIRON_DigitsAfterDotStat, ui->spinPrecision->value());

    // ODBC tests & logging
    s->setValue(SKEY_MISC_DoNotUseSqlFetchAbsolute, ui->chkNotSqlFetch->isChecked()?1:0);
    s->setValue(SKEY_MISC_OdbcUseSystemDsn, ui->rbDsnSystem->isChecked()?1:0);
    s->setValue(SKEY_MISC_OdbcConnectionPooling, ui->chkEnableConnectionPooling->isChecked()?1:0);

    // RMA / Logging
    s->setValue(SKEY_LOGGING_RecordPrimaryRMAErrors, ui->rbRequestBackup->isChecked()?1:0);
    s->setValue(SKEY_LOGGING_LogStateChanges, ui->chkLogAboutInactive->isChecked()?1:0);

    // Update check
    s->setValue(SKEY_UPDATE_AutoMode, ui->rbNoUpdates->isChecked()?1:0);

    // SSL options
    s->setValue(SKEY_MISC_sslAnyHostPOP3, ui->chkAcceptInvalidHostsPop3->isChecked()?1:0);
    s->setValue(SKEY_MISC_sslAnyDatePOP3, ui->chkAcceptInvalidDatesPop3->isChecked()?1:0);
    s->setValue(SKEY_MISC_sslAnyAuthPOP3, ui->chkIgnoreAuthorityPop3->isChecked()?1:0);
    s->setValue(SKEY_MISC_sslAnyHostIMAP, ui->chkAcceptInvalidHostsImap->isChecked()?1:0);
    s->setValue(SKEY_MISC_sslAnyDateIMAP, ui->chkAcceptInvalidDatesImap->isChecked()?1:0);
    s->setValue(SKEY_MISC_sslAnyAuthIMAP, ui->chkIgnoreAuthorityImap->isChecked()?1:0);
    s->setValue(SKEY_MISC_sslAnyHostLDAP, ui->chkAcceptInvalidHostsLdap->isChecked()?1:0);
    s->setValue(SKEY_MISC_sslAnyDateLDAP, ui->chkAcceptInvalidDatesLdap->isChecked()?1:0);
    s->setValue(SKEY_MISC_sslAnyAuthLDAP, ui->chkIgnoreAuthorityLdap->isChecked()?1:0);

    // Settings for URL tests
    s->setValue(SKEY_HOSTMON_CheckInternetConnection, ui->chkNotCheckConnection->isChecked()?1:0);
    s->setValue(SKEY_MISC_DefAgentName, ui->cmbAgentName->currentText());
    s->setValue(SKEY_MISC_IgnoreCertCnInvalid, ui->chkAcceptInvalidHosts->isChecked()?1:0);
    s->setValue(SKEY_MISC_IgnoreCertDateInvalid, ui->chkAcceptInvalidDates->isChecked()?1:0);

    // Settings for UNC tests
    s->setValue(SKEY_MISC_UncRetries, ui->spinUncRetries->value());
    int uncStatus = 0; // ui->rbUncNormal->isChecked()
    if (ui->rbUncOnePerServer->isChecked()) {
        uncStatus = 1;
    } else if (ui->rbUncOneByOne->isChecked()) {
        uncStatus = 2;
    }
    s->setValue(SKEY_MISC_UncMode, uncStatus);
    s->setValue(SKEY_MISC_UncShowErrors, ui->chkErrorInReply->isChecked()?1:0);

    // NT event log tests
    s->setValue(SKEY_MISC_ShowNTEventDescr, ui->chkShowEventsDecription->isChecked()?1:0);

    // Performance counter
    int performanceTestMode = 0; // ui->rbModeMultiThread->isChecked()
    if(ui->rbModeOneByOne->isChecked()) {
        performanceTestMode = 1;
    } else if(ui->rbModeSmart->isChecked()) {
        performanceTestMode = 2;
    } else if(ui->rbModeExternal->isChecked()) {
        performanceTestMode = 3;
    }
    s->setValue(SKEY_MISC_PerfWorkMode, performanceTestMode);

    // SNMP Get tests
    s->setValue(SKEY_MISC_SnmpAutoSingleInstance, ui->chkSnmpAppend0->isChecked()?1:0);

    // SNMP Trap tests
    s->setValue(SKEY_TRAP_Port, ui->spinSnmpTrapUdpPort->value());
    s->setValue(SKEY_TRAP_TrafficCheck, ui->grpSnmpTrafficAlert->isChecked()?1:0);
    s->setValue(SKEY_TRAP_TrafficLimit, ui->spinSnmpAlertMessages->value());
    s->setValue(SKEY_TRAP_TrafficSpan, ui->spinSnmpAlertSeconds->value());
    s->setValue(SKEY_TRAP_Pause, ui->chkSnmpSuspend->isChecked()?1:0);
    s->setValue(SKEY_TRAP_PauseSpan, ui->spinSnmpSuspendTime->value());
    s->setValue(SKEY_TRAP_Action, ui->chkExecuteAtionProfile->isChecked()?1:0);
    s->setValue(SKEY_TRAP_ActionID, ui->cmbSelectActionProfile->currentIndex());

    // Traffic monitor tests
    int trafficMonitorSelect = 0; // ui->rbTrafficInKB->isChecked()
    if(ui->rbTrafficInKbit->isChecked()) {
        trafficMonitorSelect = 1;
    } else if(ui->rbTestSettings->isChecked()) {
        trafficMonitorSelect = 2;
    }
    s->setValue(SKEY_MISC_TrafficMonitorUnits, trafficMonitorSelect);
}

/******************************************************************/

void MiscellaneousOptionsWidget::on_tableMisc_cellClicked(int row, int column)
{
    int idx = column * 5 + row;
    if (idx < ui->swMisc->count()) {
        ui->swMisc->setCurrentIndex(idx);
    }
}

/******************************************************************/

void MiscellaneousOptionsWidget::on_selectDateFormat()
{
    if (ui->chkDateTimeFixed->isChecked())
    {
        ui->lblDateFormat->setEnabled(true);
        ui->cmbDateFormat->setEnabled(true);
        ui->lblTimeFormat->setEnabled(true);
        ui->cmbTimeFormat->setEnabled(true);
    }
    else
    {
        ui->lblDateFormat->setDisabled(true);
        ui->cmbDateFormat->setDisabled(true);
        ui->lblTimeFormat->setDisabled(true);
        ui->cmbTimeFormat->setDisabled(true);
    }

}

/******************************************************************/

} // namespace SDPO


