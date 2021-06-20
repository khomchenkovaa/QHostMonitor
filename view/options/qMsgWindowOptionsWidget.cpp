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
    ui->spinMWCloseAfter->setValue(s->value(SKEY_HOSTMON_MsgWinTime, SVAL_HOSTMON_MsgWinTime).toInt());
    ui->spinMsgWinX->setValue     (s->value(SKEY_HOSTMON_MsgWinXPos, SVAL_HOSTMON_MsgWinXPos).toInt());
    ui->spinMsgWinY->setValue     (s->value(SKEY_HOSTMON_MsgWinYPos, SVAL_HOSTMON_MsgWinYPos).toInt());
    if (s->value(SKEY_HOSTMON_MsgWinConstPos, SVAL_HOSTMON_MsgWinConstPos).toInt()) {
        ui->rbMWPredefinedPosition->setChecked(true);
    } else {
        ui->rbMWShowInLastPosition->setChecked(true);
    }
    if (s->value(SKEY_HOSTMON_MsgWinCloseAuto, SVAL_HOSTMON_MsgWinCloseAuto).toInt() == 1) {
        ui->rbMWCloseAfter->setChecked(true);
    } else {
        ui->rbMWCloseManually->setChecked(true);
    }
    ui->chkMWStayOnTop->setChecked(s->value(SKEY_HOSTMON_MsgWinStayTop, SVAL_HOSTMON_MsgWinStayTop).toInt()==1);
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
