#include "qSendDataToTcpUdpPortWidget.h"
#include "ui_qSendDataToTcpUdpPortWidget.h"
#include "action/tSendDataToTcpUdpPortAction.h"

#include "qMacroEditorDlg.h"

namespace SDPO {

/******************************************************************/

SendDataToTcpUdpPortWidget::SendDataToTcpUdpPortWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SendDataToTcpUdpPortWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SendDataToTcpUdpPortWidget::~SendDataToTcpUdpPortWidget()
{
    delete ui;
}

/******************************************************************/

void SendDataToTcpUdpPortWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::SendData) {
        return;
    }
    SendDataToTcpUdpPortAction *action = qobject_cast<SendDataToTcpUdpPortAction *>(item);
    ui->cmbServer->setCurrentText(action->getServer());
    ui->cmbProtocol->setCurrentText(action->getProtocol());
    ui->spinPort->setValue(action->getPort());
    ui->cmbInitPacket->setCurrentText(action->getInitPacket());
    ui->spinWaitForAnswer->setValue(action->getWaitForAnswer());
    ui->cmbFinalPacket->setCurrentText(action->getFinalPacket());
}

/******************************************************************/

TestAction *SendDataToTcpUdpPortWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::SendData) {
        item = new SendDataToTcpUdpPortAction();
    }
    SendDataToTcpUdpPortAction *action = qobject_cast<SendDataToTcpUdpPortAction *>(item);
    action->setServer(ui->cmbServer->currentText());
    action->setProtocol(ui->cmbProtocol->currentText());
    action->setPort(ui->spinPort->value());
    action->setInitPacket(ui->cmbInitPacket->currentText());
    action->setWaitForAnswer(ui->spinWaitForAnswer->value());
    action->setFinalPacket(ui->cmbFinalPacket->currentText());
    return action;
}

/******************************************************************/

void SendDataToTcpUdpPortWidget::on_btnInitPacket_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Init packet to send"));
    dlg.setScript(ui->cmbInitPacket->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbInitPacket->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void SendDataToTcpUdpPortWidget::on_btnFinalPacket_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Final packet to send"));
    dlg.setScript(ui->cmbFinalPacket->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbFinalPacket->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

} // namespace SDPO
