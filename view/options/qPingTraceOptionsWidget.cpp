#include "qPingTraceOptionsWidget.h"
#include "ui_qPingTraceOptionsWidget.h"

namespace SDPO {

/******************************************************************/

PingTraceOptionsWidget::PingTraceOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::PingTraceOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

PingTraceOptionsWidget::~PingTraceOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void PingTraceOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::Ping_Trace, Settings::Packets, QVariant(1));
    ui->slidePackets->setValue(value.toInt());
    ui->spinPackets->setValue(value.toInt());

    value = Settings::get(Settings::Ping_Trace, Settings::PacketSize, QVariant(32));
    ui->slidePacketSize->setValue(value.toInt());
    ui->spinPacketSize->setValue(value.toInt());

    value = Settings::get(Settings::Ping_Trace, Settings::Timeout, QVariant(1000));
    ui->slideTimeout->setValue(value.toInt());
    ui->spinTimeout->setValue(value.toInt());

    value = Settings::get(Settings::Ping_Trace, Settings::TTL, QVariant(255));
    ui->slideTTL->setValue(value.toInt());
    ui->spinTTL->setValue(value.toInt());

    value = Settings::get(Settings::Ping_Trace, Settings::Hops, QVariant(32));
    ui->slideHops->setValue(value.toInt());
    ui->spinHops->setValue(value.toInt());

    value = Settings::get(Settings::Environ, Settings::ShowHostsDescription, QVariant(1));
    ui->cbShowHostDescription->setChecked(value.toInt()==1);

    value = Settings::get(Settings::Environ, Settings::ClearOldInfo, QVariant(0));
    ui->cbClearOldInfo->setChecked(value.toInt()==1);

    value = Settings::get(Settings::Ping_Trace, Settings::StopTrace, QVariant(1));
    ui->cbStopTrace->setChecked(value.toInt()==1);
}

/******************************************************************/

void PingTraceOptionsWidget::prepareToSave()
{
    Settings::set(Settings::Ping_Trace, Settings::Packets) = QVariant(ui->slidePackets->value());
    Settings::set(Settings::Ping_Trace, Settings::PacketSize) = QVariant(ui->slidePacketSize->value());
    Settings::set(Settings::Ping_Trace, Settings::Timeout) = QVariant(ui->slideTimeout->value());
    Settings::set(Settings::Ping_Trace, Settings::TTL) = QVariant(ui->slideTTL->value());
    Settings::set(Settings::Ping_Trace, Settings::Hops) = QVariant(ui->slideHops->value());
    Settings::set(Settings::Environ, Settings::ShowHostsDescription) = QVariant(ui->cbShowHostDescription->isChecked()?1:0);
    Settings::set(Settings::Environ, Settings::ClearOldInfo) = QVariant(ui->cbClearOldInfo->isChecked()?1:0);
    Settings::set(Settings::Ping_Trace, Settings::StopTrace) = QVariant(ui->cbStopTrace->isChecked()?1:0);

}

/******************************************************************/

} // namespace SDPO
