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

void PingTraceOptionsWidget::init(QSettings *s)
{
    QVariant val;
    val = s->value(SKEY_PING_Packets, SVAL_PING_Packets);
    ui->slidePackets->setValue(val.toInt());
    ui->spinPackets->setValue(val.toInt());

    val = s->value(SKEY_PING_PacketSize, SVAL_PING_PacketSize);
    ui->slidePacketSize->setValue(val.toInt());
    ui->spinPacketSize->setValue(val.toInt());

    val = s->value(SKEY_PING_Timeout, SVAL_PING_Timeout);
    ui->slideTimeout->setValue(val.toInt());
    ui->spinTimeout->setValue(val.toInt());

    val = s->value(SKEY_PING_TTL, SVAL_PING_TTL);
    ui->slideTTL->setValue(val.toInt());
    ui->spinTTL->setValue(val.toInt());

    val = s->value(SKEY_PING_Hops, SVAL_PING_Hops);
    ui->slideHops->setValue(val.toInt());
    ui->spinHops->setValue(val.toInt());

    val = s->value(SKEY_PING_ShowHostsDescription, SVAL_PING_ShowHostsDescription);
    ui->cbShowHostDescription->setChecked(val.toInt());

    val = s->value(SKEY_PING_ClearOldInfo, SVAL_PING_ClearOldInfo);
    ui->cbClearOldInfo->setChecked(val.toInt());

    val = s->value(SKEY_PING_StopTrace, SVAL_PING_StopTrace);
    ui->cbStopTrace->setChecked(val.toInt());
}

/******************************************************************/

void PingTraceOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_PING_Packets, ui->slidePackets->value());
    s->setValue(SKEY_PING_PacketSize, ui->slidePacketSize->value());
    s->setValue(SKEY_PING_Timeout, ui->slideTimeout->value());
    s->setValue(SKEY_PING_TTL, ui->slideTTL->value());
    s->setValue(SKEY_PING_Hops, ui->slideHops->value());
    s->setValue(SKEY_PING_ShowHostsDescription, ui->cbShowHostDescription->isChecked()?1:0);
    s->setValue(SKEY_PING_ClearOldInfo, ui->cbClearOldInfo->isChecked()?1:0);
    s->setValue(SKEY_PING_StopTrace, ui->cbStopTrace->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
