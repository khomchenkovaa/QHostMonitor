#include "qActiveRmaServerOptionsWidget.h"
#include "ui_qActiveRmaServerOptionsWidget.h"

namespace SDPO {

/******************************************************************/

ActiveRmaServerOptionsWidget::ActiveRmaServerOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::ActiveRmaServerOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

ActiveRmaServerOptionsWidget::~ActiveRmaServerOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void ActiveRmaServerOptionsWidget::init(QSettings *s)
{
    ui->chkActiveRmaConnection->setChecked(s->value(SKEY_RMA_Enabled,SVAL_RMA_Enabled).toInt());
    ui->spinActiveRmaPort->setValue(s->value(SKEY_RMA_Port,SVAL_RMA_Port).toInt());
    if (s->value(SKEY_RMA_AcceptAnyIP,SVAL_RMA_AcceptAnyIP).toInt()) {
        ui->rdActiveRmaAnyIp->setChecked(true);
    } else {
        ui->rdActiveRmaFollowingIp->setChecked(true);
    }
    ui->chkActiveRmaAcceptedConnections->setChecked(s->value(SKEY_RMA_LogAccepted,SVAL_RMA_LogAccepted).toInt());
    ui->chkActiveRmaRejectedConnections->setChecked(s->value(SKEY_RMA_LogRejected,SVAL_RMA_LogRejected).toInt());
}
/******************************************************************/

void ActiveRmaServerOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_RMA_Enabled, ui->chkActiveRmaConnection->isChecked()?1:0);
    s->setValue(SKEY_RMA_Port, ui->spinActiveRmaPort->value());
    s->setValue(SKEY_RMA_AcceptAnyIP,ui->rdActiveRmaAnyIp->isChecked()?1:0);
    s->setValue(SKEY_RMA_LogAccepted, ui->chkActiveRmaAcceptedConnections->isChecked()?1:0);
    s->setValue(SKEY_RMA_LogRejected, ui->chkActiveRmaRejectedConnections->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
