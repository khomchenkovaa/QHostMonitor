#include "qTrafficMonitorWidget.h"
#include "ui_qTrafficMonitorWidget.h"
#include "qTrafficSnmpCredentialsDlg.h"
#include "qTrafficNetworkInterfaceDlg.h"

namespace SDPO {

/******************************************************************/

TrafficMonitorWidget::TrafficMonitorWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::TrafficMonitorWidget)
{
    ui->setupUi(this);
    ui->cmbAlertSelect->setCurrentIndex(0);
    on_cmbAlertSelect_currentIndexChanged(0);
}

/******************************************************************/

TrafficMonitorWidget::~TrafficMonitorWidget()
{
    delete ui;
}

/******************************************************************/

void TrafficMonitorWidget::on_btnSnmpCredentials_clicked()
{
    TrafficSnmpCredentialsDlg dlg;
    dlg.exec();
}

/******************************************************************/

void TrafficMonitorWidget::on_btnNetworkInterface_clicked()
{
    TrafficNetworkInterfaceDlg dlg;
    dlg.exec();
}

/******************************************************************/

void TrafficMonitorWidget::on_cmbAlertSelect_currentIndexChanged(int index)
{
    ui->cmbAlertKbMb->setHidden(true);
    ui->cmbAlertPkt->setHidden(true);
    ui->cmbAlertPkt->setDisabled(true);
    ui->cmbAlertPktT->setHidden(true);
    switch (index) {
    case 0: // In/Out traffic
    case 1: // Income traffic
    case 2: // Outgoing traffic
        ui->cmbAlertKbMb->setHidden(false);
        break;
    case 3: // In Discards
    case 4: // In Errors
    case 5: // Out Discards
    case 6: // Out Errors
        ui->cmbAlertPktT->setHidden(false);
        break;
    case 7: // Output queue
        ui->cmbAlertPkt->setHidden(false);
        break;
    }
}

/******************************************************************/

} // namespace SDPO


