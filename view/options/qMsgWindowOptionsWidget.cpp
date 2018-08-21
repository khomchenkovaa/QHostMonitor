#include "qMsgWindowOptionsWidget.h"
#include "ui_qMsgWindowOptionsWidget.h"

namespace SDPO {

/******************************************************************/

MsgWindowOptionsWidget::MsgWindowOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::MsgWindowOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

MsgWindowOptionsWidget::~MsgWindowOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void MsgWindowOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::HostMon, Settings::MsgWinTime, QVariant(5));
    ui->spinMWCloseAfter->setValue(value.toInt());

    value = Settings::get(Settings::HostMon, Settings::MsgWinXPos, QVariant(200));
    ui->spinMsgWinX->setValue(value.toInt());

    value = Settings::get(Settings::HostMon, Settings::MsgWinYPos, QVariant(100));
    ui->spinMsgWinY->setValue(value.toInt());

    value = Settings::get(Settings::HostMon, Settings::MsgWinConstPos, QVariant(0));
    if (value.toInt() == 1) {
        ui->rbMWPredefinedPosition->setChecked(true);
    } else {
        ui->rbMWShowInLastPosition->setChecked(true);
    }

    value = Settings::get(Settings::HostMon, Settings::MsgWinCloseAuto, QVariant(1));
    if (value.toInt() == 1) {
        ui->rbMWCloseAfter->setChecked(true);
    } else {
        ui->rbMWCloseManually->setChecked(true);
    }

    value = Settings::get(Settings::HostMon, Settings::MsgWinStayTop, QVariant(1));
    ui->chkMWStayOnTop->setChecked(value.toInt()==1);
}

/******************************************************************/

void MsgWindowOptionsWidget::prepareToSave()
{
    Settings::set(Settings::HostMon, Settings::MsgWinTime) = QVariant(ui->spinMWCloseAfter->value());
    Settings::set(Settings::HostMon, Settings::MsgWinXPos) = QVariant(ui->spinMsgWinX->value());
    Settings::set(Settings::HostMon, Settings::MsgWinYPos) = QVariant(ui->spinMsgWinY->value());
    Settings::set(Settings::HostMon, Settings::MsgWinConstPos) = QVariant(ui->rbMWPredefinedPosition->isChecked()?1:0);
    Settings::set(Settings::HostMon, Settings::MsgWinCloseAuto) = QVariant(ui->rbMWCloseAfter->isChecked()?1:0);
    Settings::set(Settings::HostMon, Settings::MsgWinStayTop) = QVariant(ui->chkMWStayOnTop->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
