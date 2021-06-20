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

void RciOptionsWidget::init(QSettings *s)
{
    ui->chkRciOptionsEnable->setChecked             (s->value(SKEY_RCI_Enabled, SVAL_RCI_Enabled).toInt());
    on_checkedRemoteControle();
    connect(ui->chkRciOptionsEnable, SIGNAL(clicked()),this,SLOT(on_checkedRemoteControle()));
    ui->spinIncomingConnectionsPort->setValue       (s->value(SKEY_RCI_Port, SVAL_RCI_Port).toInt());
    ui->spinMaximumSimultaneousConnections->setValue(s->value(SKEY_RCI_MaxClients, SVAL_RCI_MaxClients).toInt());
    ui->spinTimeout->setValue                       (s->value(SKEY_RCI_Timeout, SVAL_RCI_Timeout).toInt());
    ui->chkRecordInfoAcceptedConnections->setChecked(s->value(SKEY_RCI_LogAccepted, SVAL_RCI_LogAccepted).toInt());
    ui->chkIncludingWatchDogAccount_1->setChecked   (s->value(SKEY_RCI_LogAcceptedWatchDog, SVAL_RCI_LogAcceptedWatchDog).toInt());
    ui->chkRecordInfoRejectedConnections->setChecked(s->value(SKEY_RCI_LogRejected, SVAL_RCI_LogRejected).toInt());
    ui->chkIncludingWatchDogAccount_2->setChecked   (s->value(SKEY_RCI_LogRejectedWatchDog, SVAl_RCI_LogRejectedWatchDog).toInt());
    ui->chkRecordInfoAcceptedCommands->setChecked   (s->value(SKEY_RCI_LogSuccess, SVAL_RCI_LogSuccess).toInt());
    ui->chkRecordInfoRejectedCommands->setChecked   (s->value(SKEY_RCI_LogError, SVAL_RCI_LogError).toInt());
}

/******************************************************************/

void RciOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_RCI_Enabled, ui->chkRciOptionsEnable->isChecked()?1:0);
    s->setValue(SKEY_RCI_Port, ui->spinIncomingConnectionsPort->value());
    s->setValue(SKEY_RCI_MaxClients, ui->spinMaximumSimultaneousConnections->value());
    s->setValue(SKEY_RCI_Timeout, ui->spinTimeout->value());
    s->setValue(SKEY_RCI_LogAccepted, ui->chkRecordInfoAcceptedConnections->isChecked()?1:0);
    s->setValue(SKEY_RCI_LogAcceptedWatchDog, ui->chkIncludingWatchDogAccount_1->isChecked()?1:0);
    s->setValue(SKEY_RCI_LogRejected, ui->chkRecordInfoRejectedConnections->isChecked()?1:0);
    s->setValue(SKEY_RCI_LogRejectedWatchDog, ui->chkIncludingWatchDogAccount_2->isChecked()?1:0);
    s->setValue(SKEY_RCI_LogSuccess, ui->chkRecordInfoAcceptedCommands->isChecked()?1:0);
    s->setValue(SKEY_RCI_LogError, ui->chkRecordInfoRejectedCommands->isChecked()?1:0);
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
