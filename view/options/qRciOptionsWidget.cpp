#include "qRciOptionsWidget.h"
#include "ui_qRciOptionsWidget.h"

namespace SDPO {

/******************************************************************/

RciOptionsWidget::RciOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::RciOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

RciOptionsWidget::~RciOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void RciOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::RCI, Settings::Enabled, QVariant(0));
        if (value.toInt() == 1)
            ui->chkRciOptionsEnable->setChecked(true);
        else
            ui->chkRciOptionsEnable->setChecked(false);
        on_checkedRemoteControle();
        connect(ui->chkRciOptionsEnable, SIGNAL(clicked()),this,SLOT(on_checkedRemoteControle()));

    value = Settings::get(Settings::RCI, Settings::Port, QVariant(1054));
        ui->spinIncomingConnectionsPort->setValue(value.toInt());

    value = Settings::get(Settings::RCI, Settings::MaxClients, QVariant(16));
        ui->spinMaximumSimultaneousConnections->setValue(value.toInt());

    value = Settings::get(Settings::RCI, Settings::Port, QVariant(300));
        ui->spinTimeout->setValue(value.toInt());

    value = Settings::get(Settings::RCI, Settings::LogAccepted, QVariant(1));
        if (value.toInt() == 1)
            ui->chkRecordInfoAcceptedConnections->setChecked(true);
        else
            ui->chkRecordInfoAcceptedConnections->setChecked(false);

    value = Settings::get(Settings::RCI, Settings::LogAcceptedWatchDog, QVariant(1));
        if (value.toInt() == 1)
            ui->chkIncludingWatchDogAccount_1->setChecked(true);
        else
            ui->chkIncludingWatchDogAccount_1->setChecked(false);

    value = Settings::get(Settings::RCI, Settings::LogRejected, QVariant(1));
        if (value.toInt() == 1)
            ui->chkRecordInfoRejectedConnections->setChecked(true);
        else
            ui->chkRecordInfoRejectedConnections->setChecked(false);

    value = Settings::get(Settings::RCI, Settings::LogRejectedWatchDog, QVariant(0));
        if (value.toInt() == 1)
            ui->chkIncludingWatchDogAccount_2->setChecked(true);
        else
            ui->chkIncludingWatchDogAccount_2->setChecked(false);

    value = Settings::get(Settings::RCI, Settings::LogSuccess, QVariant(1));
        if (value.toInt() == 1)
            ui->chkRecordInfoAcceptedCommands->setChecked(true);
        else
            ui->chkRecordInfoAcceptedCommands->setChecked(false);

    value = Settings::get(Settings::RCI, Settings::LogRejected, QVariant(1));
        if (value.toInt() == 1)
            ui->chkRecordInfoRejectedCommands->setChecked(true);
        else
            ui->chkRecordInfoRejectedCommands->setChecked(false);
}

/******************************************************************/

void RciOptionsWidget::prepareToSave()
{
    Settings::set(Settings::RCI, Settings::Enabled) = QVariant(ui->chkRciOptionsEnable->isChecked()?1:0);
    Settings::set(Settings::RCI, Settings::Port) = QVariant(ui->spinIncomingConnectionsPort->value());
    Settings::set(Settings::RCI, Settings::MaxClients) = QVariant(ui->spinMaximumSimultaneousConnections->value());
    Settings::set(Settings::RCI, Settings::Timeout) = QVariant(ui->spinTimeout->value());
    Settings::set(Settings::RCI, Settings::LogAccepted) = QVariant(ui->chkRecordInfoAcceptedConnections->isChecked()?1:0);
    Settings::set(Settings::RCI, Settings::LogAcceptedWatchDog) = QVariant(ui->chkIncludingWatchDogAccount_1->isChecked()?1:0);
    Settings::set(Settings::RCI, Settings::LogRejected) = QVariant(ui->chkRecordInfoRejectedConnections->isChecked()?1:0);
    Settings::set(Settings::RCI, Settings::LogRejectedWatchDog) = QVariant(ui->chkIncludingWatchDogAccount_2->isChecked()?1:0);
    Settings::set(Settings::RCI, Settings::LogSuccess) = QVariant(ui->chkRecordInfoAcceptedCommands->isChecked()?1:0);
    Settings::set(Settings::RCI, Settings::LogError) = QVariant(ui->chkRecordInfoRejectedCommands->isChecked()?1:0);
}

/******************************************************************/

void RciOptionsWidget::on_checkedRemoteControle()
{
    if (ui->chkRciOptionsEnable->isChecked())
    {
        ui->frameSpinBox->setEnabled(true);
        ui->frameRecordsChecked->setEnabled(true);
    }
    else
    {
        ui->frameSpinBox->setDisabled(true);
        ui->frameRecordsChecked->setDisabled(true);
    }
}

/******************************************************************/

} // namespace SDPO
