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

void MsgWindowOptionsWidget::init(QSettings *s)
{
    ui->spinMWCloseAfter->setValue(s->value(SKEY_HOSTMON_MsgWinTime,5).toInt());
    ui->spinMsgWinX->setValue(s->value(SKEY_HOSTMON_MsgWinXPos,200).toInt());
    ui->spinMsgWinY->setValue(s->value(SKEY_HOSTMON_MsgWinYPos,100).toInt());
    if (s->value(SKEY_HOSTMON_MsgWinConstPos,0).toInt()) {
        ui->rbMWPredefinedPosition->setChecked(true);
    } else {
        ui->rbMWShowInLastPosition->setChecked(true);
    }
    if (s->value(SKEY_HOSTMON_MsgWinCloseAuto,1).toInt() == 1) {
        ui->rbMWCloseAfter->setChecked(true);
    } else {
        ui->rbMWCloseManually->setChecked(true);
    }
    ui->chkMWStayOnTop->setChecked(s->value(SKEY_HOSTMON_MsgWinStayTop,1).toInt()==1);
}

/******************************************************************/

void MsgWindowOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_HOSTMON_MsgWinTime, ui->spinMWCloseAfter->value());
    s->setValue(SKEY_HOSTMON_MsgWinXPos, ui->spinMsgWinX->value());
    s->setValue(SKEY_HOSTMON_MsgWinYPos, ui->spinMsgWinY->value());

    s->setValue(SKEY_HOSTMON_MsgWinConstPos, ui->rbMWPredefinedPosition->isChecked()?1:0);
    s->setValue(SKEY_HOSTMON_MsgWinCloseAuto, ui->rbMWCloseAfter->isChecked()?1:0);
    s->setValue(SKEY_HOSTMON_MsgWinStayTop, ui->chkMWStayOnTop->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
