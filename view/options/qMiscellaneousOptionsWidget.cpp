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

void MiscellaneousOptionsWidget::init()
{
        /******************************************************************/

    QVariant value = Settings::get(Settings::FixedFormats, Settings::UseFixedFormats, QVariant(0));
        if (value.toInt() == 1)
            ui->chkDateTimeFixed->setChecked(true);
        else
            ui->chkDateTimeFixed->setChecked(false);
        on_selectDateFormat();
        connect(ui->chkDateTimeFixed, SIGNAL(clicked()),this, SLOT(on_selectDateFormat()));

    value = Settings::get(Settings::FixedFormats, Settings::FixedDateFormat, QVariant(3));
        ui->cmbDateFormat->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::FixedFormats, Settings::FixedTimeFormat, QVariant(0));
        ui->cmbTimeFormat->setCurrentIndex(value.toInt());

        /******************************************************************/

    value = Settings::get(Settings::Reports, Settings::ShowFolders, QVariant(0));
        if (value.toInt() == 1)
            ui->chkShowFolderNames->setChecked(true);
        else
            ui->chkShowFolderNames->setChecked(false);

    value = Settings::get(Settings::Reports, Settings::SkipEmptyFolders, QVariant(1));
        if (value.toInt() == 1)
            ui->chkSkipEmptyFolders->setChecked(true);
        else
            ui->chkSkipEmptyFolders->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::AliveDeadRatioMode, QVariant(0));
        if (value.toInt() == 0)
            ui->rbDisplayRatioTests->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbDisplayRatioTime->setChecked(true);

    value = Settings::get(Settings::Environ, Settings::DigitsAfterDotStat, QVariant(2));
        ui->spinPrecision->setValue(value.toInt());

        /******************************************************************/

    value = Settings::get(Settings::Misc, Settings::DoNotUse_SqlFetchAbsolute, QVariant(1));
        if (value.toInt() == 1)
            ui->chkNotSqlFetch->setChecked(true);
        else
            ui->chkNotSqlFetch->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::ODBC_UseSystemDSN, QVariant(1));
        if (value.toInt() == 0)
            ui->rbDsnUser->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbDsnSystem->setChecked(true);

    value = Settings::get(Settings::Misc, Settings::ODBC_ConnectionPooling, QVariant(0));
        if (value.toInt() == 1)
            ui->chkEnableConnectionPooling->setChecked(true);
        else
            ui->chkEnableConnectionPooling->setChecked(false);

        /******************************************************************/

    value = Settings::get(Settings::Logging, Settings::RecordPrimaryRMAErrors, QVariant(1));
        if (value.toInt() == 0)
            ui->rbSetUnknown->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbRequestBackup->setChecked(true);

    value = Settings::get(Settings::Logging, Settings::LogStateChanges, QVariant(0));
        if (value.toInt() == 1)
            ui->chkLogAboutInactive->setChecked(true);
        else
            ui->chkLogAboutInactive->setChecked(false);

        /******************************************************************/

    value = Settings::get(Settings::UpdateCheck, Settings::AutoMode, QVariant(1));
        if (value.toInt() == 0)
            ui->rbUpdateCheck->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbNoUpdates->setChecked(true);

        /******************************************************************/

    value = Settings::get(Settings::Misc, Settings::sslAnyHostPOP3, QVariant(0));
        if (value.toInt() == 1)
            ui->chkAcceptInvalidHostsPop3->setChecked(true);
        else
            ui->chkAcceptInvalidHostsPop3->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::sslAnyDatePOP3, QVariant(0));
        if (value.toInt() == 1)
            ui->chkAcceptInvalidDatesPop3->setChecked(true);
        else
            ui->chkAcceptInvalidDatesPop3->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::sslAnyAuthPOP3, QVariant(0));
        if (value.toInt() == 1)
            ui->chkIgnoreAuthorityPop3->setChecked(true);
        else
            ui->chkIgnoreAuthorityPop3->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::sslAnyHostIMAP, QVariant(0));
        if (value.toInt() == 1)
            ui->chkAcceptInvalidHostsImap->setChecked(true);
        else
            ui->chkAcceptInvalidHostsImap->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::sslAnyDateIMAP, QVariant(0));
        if (value.toInt() == 1)
            ui->chkAcceptInvalidDatesImap->setChecked(true);
        else
            ui->chkAcceptInvalidDatesImap->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::sslAnyAuthIMAP, QVariant(0));
        if (value.toInt() == 1)
            ui->chkIgnoreAuthorityImap->setChecked(true);
        else
            ui->chkIgnoreAuthorityImap->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::sslAnyHostLDAP, QVariant(0));
        if (value.toInt() == 1)
            ui->chkAcceptInvalidHostsLdap->setChecked(true);
        else
            ui->chkAcceptInvalidHostsLdap->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::sslAnyDateLDAP, QVariant(0));
        if (value.toInt() == 1)
            ui->chkAcceptInvalidDatesLdap->setChecked(true);
        else
            ui->chkAcceptInvalidDatesLdap->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::sslAnyAuthLDAP, QVariant(0));
        if (value.toInt() == 1)
            ui->chkIgnoreAuthorityLdap->setChecked(true);
        else
            ui->chkIgnoreAuthorityLdap->setChecked(false);

        /******************************************************************/

    value = Settings::get(Settings::HostMon, Settings::CheckInternetConnection, QVariant(0));
        if (value.toInt() == 1)
            ui->chkNotCheckConnection->setChecked(true);
        else
            ui->chkNotCheckConnection->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::DefAgentName, QVariant(4));
        ui->cmbAgentName->setCurrentText(value.toString());

    value = Settings::get(Settings::Misc, Settings::IGNORE_CERT_CN_INVALID, QVariant(0));
        if (value.toInt() == 1)
            ui->chkAcceptInvalidHosts->setChecked(true);
        else
            ui->chkAcceptInvalidHosts->setChecked(false);

    value = Settings::get(Settings::Misc, Settings::IGNORE_CERT_DATE_INVALID, QVariant(0));
        if (value.toInt() == 1)
            ui->chkAcceptInvalidDates->setChecked(true);
        else
            ui->chkAcceptInvalidDates->setChecked(false);

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

void MiscellaneousOptionsWidget::prepareToSave()
{      
    Settings::set(Settings::FixedFormats, Settings::UseFixedFormats) = QVariant(ui->chkDateTimeFixed->isChecked()?1:0);
    Settings::set(Settings::FixedFormats, Settings::FixedDateFormat) = QVariant(ui->cmbDateFormat->currentIndex());
    Settings::set(Settings::FixedFormats, Settings::FixedTimeFormat) = QVariant(ui->cmbTimeFormat->currentIndex());
    Settings::set(Settings::Reports, Settings::ShowFolders) = QVariant(ui->chkShowFolderNames->isChecked()?1:0);
    Settings::set(Settings::Reports, Settings::SkipEmptyFolders) = QVariant(ui->chkSkipEmptyFolders->isChecked()?1:0);

    int DisplayRatio;
        if(ui->rbDisplayRatioTests->isChecked())
            DisplayRatio = 0;
        else if (ui->rbDisplayRatioTime->isChecked())
            DisplayRatio = 1;
    Settings::set(Settings::Misc, Settings::AliveDeadRatioMode) = QVariant(DisplayRatio);
    Settings::set(Settings::Environ, Settings::DigitsAfterDotStat) = QVariant(ui->spinPrecision->value());
    Settings::set(Settings::Misc, Settings::DoNotUse_SqlFetchAbsolute) = QVariant(ui->chkNotSqlFetch->isChecked()?1:0);

    int DsnSelect;
        if(ui->rbDsnUser->isChecked())
            DsnSelect = 0;
        else if (ui->rbDsnSystem->isChecked())
            DsnSelect = 1;
    Settings::set(Settings::Misc, Settings::ODBC_UseSystemDSN) = QVariant(DsnSelect);
    Settings::set(Settings::Misc, Settings::ODBC_ConnectionPooling) = QVariant(ui->chkEnableConnectionPooling->isChecked()?1:0);
    Settings::set(Settings::Logging, Settings::LogStateChanges) = QVariant(ui->chkLogAboutInactive->isChecked()?1:0);

    int primaryRmaFailed;
        if(ui->rbSetUnknown->isChecked())
            primaryRmaFailed = 0;
        else if (ui->rbRequestBackup->isChecked())
            primaryRmaFailed = 1;
    Settings::set(Settings::Logging, Settings::RecordPrimaryRMAErrors) = QVariant(primaryRmaFailed);

    int updateCheck;
    if (ui->rbUpdateCheck->isChecked())
        updateCheck = 0;
    else if (ui->rbNoUpdates->isChecked())
        updateCheck = 1;
    Settings::set(Settings::UpdateCheck, Settings::AutoMode) = QVariant(updateCheck);
    Settings::set(Settings::Misc, Settings::sslAnyHostPOP3) = QVariant(ui->chkAcceptInvalidHostsPop3->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::sslAnyDatePOP3) = QVariant(ui->chkAcceptInvalidDatesPop3->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::sslAnyAuthPOP3) = QVariant(ui->chkIgnoreAuthorityPop3->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::sslAnyHostIMAP) = QVariant(ui->chkAcceptInvalidHostsImap->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::sslAnyDateIMAP) = QVariant(ui->chkAcceptInvalidDatesImap->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::sslAnyAuthIMAP) = QVariant(ui->chkIgnoreAuthorityImap->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::sslAnyHostLDAP) = QVariant(ui->chkAcceptInvalidHostsLdap->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::sslAnyDateLDAP) = QVariant(ui->chkAcceptInvalidDatesLdap->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::sslAnyAuthLDAP) = QVariant(ui->chkIgnoreAuthorityLdap->isChecked()?1:0);
    Settings::set(Settings::HostMon, Settings::CheckInternetConnection) = QVariant(ui->chkNotCheckConnection->isChecked()?1:0);
    Settings::set(Settings::HostMon, Settings::CheckInternetConnection) = QVariant(ui->chkNotCheckConnection->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::DefAgentName) = QVariant(ui->cmbAgentName->currentText());
    Settings::set(Settings::Misc, Settings::IGNORE_CERT_CN_INVALID) = QVariant(ui->chkAcceptInvalidHosts->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::IGNORE_CERT_DATE_INVALID) = QVariant(ui->chkAcceptInvalidDates->isChecked()?1:0);
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


