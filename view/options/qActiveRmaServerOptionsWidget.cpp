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
    ui->chkActiveRmaConnection->setChecked(s->value(SKEY_RMA_Enabled,0).toInt());
    ui->spinActiveRmaPort->setValue(s->value(SKEY_RMA_Port,5056).toInt());
    if (s->value(SKEY_RMA_AcceptAnyIP,1).toInt()) {
        ui->rdActiveRmaAnyIp->setChecked(true);
    } else {
        ui->rdActiveRmaFollowingIp->setChecked(true);
    }
    ui->chkActiveRmaAcceptedConnections->setChecked(s->value(SKEY_RMA_LogAccepted,0).toInt());
    ui->chkActiveRmaRejectedConnections->setChecked(s->value(SKEY_RMA_LogRejected,0).toInt());
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
