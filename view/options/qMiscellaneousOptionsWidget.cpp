#include "qMiscellaneousOptionsWidget.h"
#include "ui_qMiscellaneousOptionsWidget.h"
#include "qActionProfiles.h"
#include "global/ioActionProfileLoader.h"
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
    QVariant value;

    // Date & Time format
    ui->chkDateTimeFixed->setChecked(s->value(SKEY_FORMATS_UseFixedFormats,0).toInt());
    on_selectDateFormat();
    connect(ui->chkDateTimeFixed, SIGNAL(clicked()),this, SLOT(on_selectDateFormat()));
    ui->cmbDateFormat->setCurrentIndex(s->value(SKEY_FORMATS_FixedDateFormat,3).toInt());
    ui->cmbTimeFormat->setCurrentIndex(s->value(SKEY_FORMATS_FixedTimeFormat,0).toInt());

    // Reports & Statistics
    ui->chkShowFolderNames->setChecked(s->value(SKEY_REPORTS_ShowFolders,0).toInt());
    ui->chkSkipEmptyFolders->setChecked(s->value(SKEY_REPORTS_SkipEmptyFolders,1).toInt());
    if (s->value(SKEY_MISC_AliveDeadRatioMode,0).toInt()) {
        ui->rbDisplayRatioTime->setChecked(true);
    } else {
        ui->rbDisplayRatioTests->setChecked(true);
    }
    ui->spinPrecision->setValue(s->value(SKEY_ENVIRON_DigitsAfterDotStat,2).toInt());

    // ODBC tests & logging
    ui->chkNotSqlFetch->setChecked(s->value(SKEY_MISC_DoNotUseSqlFetchAbsolute,1).toInt());
    if(s->value(SKEY_MISC_ODBCUseSystemDSN,1).toInt()) {
        ui->rbDsnSystem->setChecked(true);
    } else {
        ui->rbDsnUser->setChecked(true);
    }
    ui->chkEnableConnectionPooling->setChecked(s->value(SKEY_MISC_ODBCConnectionPooling,0).toInt());

    // RMA / Logging
    if (s->value(SKEY_LOGGING_RecordPrimaryRMAErrors,1).toInt()) {
        ui->rbRequestBackup->setChecked(true);
    } else {
        ui->rbSetUnknown->setChecked(true);
    }
    ui->chkLogAboutInactive->setChecked(s->value(SKEY_LOGGING_LogStateChanges,0).toInt());

    // Update check
    if (s->value(SKEY_UPDATE_AutoMode,1).toInt()) {
        ui->rbNoUpdates->setChecked(true);
    } else {
        ui->rbUpdateCheck->setChecked(true);
    }

    // SSL options
    ui->chkAcceptInvalidHostsPop3->setChecked(s->value(SKEY_MISC_sslAnyHostPOP3,0).toInt());
    ui->chkAcceptInvalidDatesPop3->setChecked(s->value(SKEY_MISC_sslAnyDatePOP3,0).toInt());
    ui->chkIgnoreAuthorityPop3->setChecked(s->value(SKEY_MISC_sslAnyAuthPOP3,0).toInt());
    ui->chkAcceptInvalidHostsImap->setChecked(s->value(SKEY_MISC_sslAnyHostIMAP,0).toInt());
    ui->chkAcceptInvalidDatesImap->setChecked(s->value(SKEY_MISC_sslAnyDateIMAP,0).toInt());
    ui->chkIgnoreAuthorityImap->setChecked(s->value(SKEY_MISC_sslAnyAuthIMAP,0).toInt());
    ui->chkAcceptInvalidHostsLdap->setChecked(s->value(SKEY_MISC_sslAnyHostLDAP,0).toInt());
    ui->chkAcceptInvalidDatesLdap->setChecked(s->value(SKEY_MISC_sslAnyDateLDAP,0).toInt());
    ui->chkIgnoreAuthorityLdap->setChecked(s->value(SKEY_MISC_sslAnyAuthLDAP,0).toInt());

    // Settings for URL tests
    ui->chkNotCheckConnection->setChecked(s->value(SKEY_HOSTMON_CheckInternetConnection,0).toInt());
    ui->cmbAgentName->setCurrentText(s->value(SKEY_MISC_DefAgentName, "KSHostMonitor:/1.0").toString());
    ui->chkAcceptInvalidHosts->setChecked(s->value(SKEY_MISC_IgnoreCertCnInvalid,0).toInt());
    ui->chkAcceptInvalidDates->setChecked(s->value(SKEY_MISC_IgnoreCertDateInvalid,0).toInt());

        /******************************************************************/

    value = Settings::get(Settings::Misc, Settings::UNCRetries, QVariant(2));
        ui->spinUncRetries->setValue(value.toInt());

    value = Settings::get(Settings::Misc, Settings::UNCMode, QVariant(0));
        if (value.toInt() == 0)
            ui->rbUncNormal->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbUncOnePerServer->setChecked(true);
        else if (value.toInt() == 2)
            ui->rbUncOneByOne->setChecked(true);

    value = Settings::get(Settings::Misc, Settings::UNCShowErrors, QVariant(0));
        if (value.toInt() == 1)
            ui->chkErrorInReply->setChecked(true);
        else
            ui->chkErrorInReply->setChecked(false);

        /******************************************************************/

    value = Settings::get(Settings::Misc, Settings::ShowNTEventDescr, QVariant(1));
        if (value.toInt() == 1)
            ui->chkShowEventsDecription->setChecked(true);
        else
            ui->chkShowEventsDecription->setChecked(false);

        /******************************************************************/
    value = Settings::get(Settings::Misc, Settings::PerfWorkMode, QVariant(0));
        if (value.toInt() == 0)
            ui->rbModeMultiThread->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbModeOneByOne->setChecked(true);
        else if (value.toInt() == 2)
            ui->rbModeSmart->setChecked(true);
        else if (value.toInt() == 3)
            ui->rbModeExternal->setChecked(true);

       /******************************************************************/
    value = Settings::get(Settings::Misc, Settings::snmpAutoSingleInstance, QVariant(0));
        if (value.toInt() == 1)
            ui->chkSnmpAppend0->setChecked(true);
        else
            ui->chkSnmpAppend0->setChecked(false);

       /******************************************************************/

     reset_SnmpTrapAction();

     value = Settings::get(Settings::TrapListener, Settings::Port, QVariant(162));
        ui->spinSnmpTrapUdpPort->setValue(value.toInt());

     value = Settings::get(Settings::TrapListener, Settings::TrafficCheck, QVariant(1));
        if (value.toInt() == 1)
            ui->grpSnmpTrafficAlert->setChecked(true);
        else
            ui->grpSnmpTrafficAlert->setChecked(false);

     value = Settings::get(Settings::TrapListener, Settings::TrafficLimit, QVariant(1800));
        ui->spinSnmpAlertMessages->setValue(value.toInt());

     value = Settings::get(Settings::TrapListener, Settings::TrafficSpan, QVariant(60));
     ui->spinSnmpAlertSeconds->setValue(value.toInt());

     value = Settings::get(Settings::TrapListener, Settings::Pause, QVariant(1));
        if (value.toInt() == 1)
            ui->chkSnmpSuspend->setChecked(true);
        else
            ui->chkSnmpSuspend->setChecked(false);

     value = Settings::get(Settings::TrapListener, Settings::PauseSpan, QVariant(60));
     ui->spinSnmpSuspendTime->setValue(value.toInt());

     value = Settings::get(Settings::TrapListener, Settings::Action, QVariant(1));
        if (value.toInt() == 1)
            ui->chkExecuteAtionProfile->setChecked(true);
        else
            ui->chkExecuteAtionProfile->setChecked(false);

     value = Settings::get(Settings::TrapListener, Settings::ActionID, QVariant());
        ui->cmbSelectActionProfile->setCurrentIndex(value.toInt());

        /******************************************************************/

    value = Settings::get(Settings::Misc, Settings::TrafficMonitorUnits, QVariant(0));
        if (value.toInt() == 0)
            ui->rbTrafficInKB->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbTrafficInKbit->setChecked(true);
        else if (value.toInt() == 2)
            ui->rbTestSettings->setChecked(true);
}

/******************************************************************/

void MiscellaneousOptionsWidget::prepareToSave(QSettings *s)
{      
    // Date & Time format
    s->setValue(SKEY_FORMATS_UseFixedFormats, ui->chkDateTimeFixed->isChecked()?1:0);
    s->setValue(SKEY_FORMATS_FixedDateFormat, ui->cmbDateFormat->currentIndex());
    s->setValue(SKEY_FORMATS_FixedTimeFormat, ui->cmbTimeFormat->currentIndex());

    // Reports & Statistics
    s->setValue(SKEY_REPORTS_ShowFolders, ui->chkShowFolderNames->isChecked()?1:0);
    s->setValue(SKEY_REPORTS_SkipEmptyFolders, ui->chkSkipEmptyFolders->isChecked()?1:0);
    s->setValue(SKEY_MISC_AliveDeadRatioMode, ui->rbDisplayRatioTime->isChecked()?1:0);
    s->setValue(SKEY_ENVIRON_DigitsAfterDotStat, ui->spinPrecision->value());

    // ODBC tests & logging
    s->setValue(SKEY_MISC_DoNotUseSqlFetchAbsolute, ui->chkNotSqlFetch->isChecked()?1:0);
    s->setValue(SKEY_MISC_ODBCUseSystemDSN, ui->rbDsnSystem->isChecked()?1:0);
    s->setValue(SKEY_MISC_ODBCConnectionPooling, ui->chkEnableConnectionPooling->isChecked()?1:0);

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


    Settings::set(Settings::Misc, Settings::UNCRetries) = QVariant(ui->spinUncRetries->value());

    int UncStatus;
        if(ui->rbUncNormal->isChecked())
            UncStatus = 0;
        else if (ui->rbUncOnePerServer->isChecked())
            UncStatus = 1;
        else if (ui->rbUncOneByOne->isChecked())
            UncStatus = 2;
    Settings::set(Settings::Misc, Settings::UNCMode) = QVariant(UncStatus);
    Settings::set(Settings::Misc, Settings::UNCShowErrors) = QVariant(ui->chkErrorInReply->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::ShowNTEventDescr) = QVariant(ui->chkShowEventsDecription->isChecked()?1:0);

    int performanceTestMode;
        if(ui->rbModeMultiThread->isChecked())
            performanceTestMode = 0;
        else if(ui->rbModeOneByOne->isChecked())
            performanceTestMode = 1;
        else if(ui->rbModeSmart->isChecked())
            performanceTestMode = 2;
        else if(ui->rbModeExternal->isChecked())
            performanceTestMode = 3;
    Settings::set(Settings::Misc, Settings::PerfWorkMode) = QVariant(performanceTestMode);
    Settings::set(Settings::Misc, Settings::snmpAutoSingleInstance) = QVariant(ui->chkSnmpAppend0->isChecked()?1:0);
    Settings::set(Settings::TrapListener, Settings::Port) = QVariant(ui->spinSnmpTrapUdpPort->value());
    Settings::set(Settings::TrapListener, Settings::TrafficCheck) = QVariant(ui->grpSnmpTrafficAlert->isChecked()?1:0);
    Settings::set(Settings::TrapListener, Settings::TrafficLimit) = QVariant(ui->spinSnmpAlertMessages->value());
    Settings::set(Settings::TrapListener, Settings::TrafficSpan) = QVariant(ui->spinSnmpAlertSeconds->value());
    Settings::set(Settings::TrapListener, Settings::Pause) = QVariant(ui->chkSnmpSuspend->isChecked()?1:0);
    Settings::set(Settings::TrapListener, Settings::PauseSpan) = QVariant(ui->spinSnmpSuspendTime->value());
    Settings::set(Settings::TrapListener, Settings::Action) = QVariant(ui->chkExecuteAtionProfile->isChecked()?1:0);
    Settings::set(Settings::TrapListener, Settings::ActionID) = QVariant(ui->cmbSelectActionProfile->currentIndex());

    int trafficMonitorSelect;
        if(ui->rbTrafficInKB->isChecked())
            trafficMonitorSelect = 0;
        else if(ui->rbTrafficInKbit->isChecked())
            trafficMonitorSelect = 1;
        else if(ui->rbTestSettings->isChecked())
            trafficMonitorSelect = 2;
        Settings::set(Settings::Misc, Settings::TrafficMonitorUnits) = QVariant(trafficMonitorSelect);
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


