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

void ActiveRmaServerOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::ActiveRMAServer, Settings::Enabled, QVariant(0));
        if (value.toInt() == 1)
            ui->chkActiveRmaConnection->setChecked(true);
        else
            ui->chkActiveRmaConnection->setChecked(false);

    value = Settings::get(Settings::ActiveRMAServer, Settings::Port, QVariant(5056));
        ui->spinActiveRmaPort->setValue(value.toInt());

    value = Settings::get(Settings::ActiveRMAServer, Settings::AcceptAnyIP, QVariant(1));
        if (value.toInt() == 1)
            ui->rdActiveRmaAnyIp->setChecked(true);
        else
            ui->rdActiveRmaFollowingIp->setChecked(true);

    value = Settings::get(Settings::ActiveRMAServer, Settings::LogAccepted, QVariant(0));
        if (value.toInt() == 1)
            ui->chkActiveRmaAcceptedConnections->setChecked(true);
        else
            ui->chkActiveRmaAcceptedConnections->setChecked(false);

    value = Settings::get(Settings::ActiveRMAServer, Settings::LogAccepted, QVariant(0));
        if (value.toInt() == 1)
            ui->chkActiveRmaRejectedConnections->setChecked(true);
        else
            ui->chkActiveRmaRejectedConnections->setChecked(false);

}
/******************************************************************/

void ActiveRmaServerOptionsWidget::prepareToSave()
{
    Settings::set(Settings::ActiveRMAServer, Settings::Enabled) = QVariant(ui->chkActiveRmaConnection->isChecked()?1:0);
    Settings::set(Settings::ActiveRMAServer, Settings::Port) = QVariant(ui->spinActiveRmaPort->value());

    int acceptConnections;
        if (ui->rdActiveRmaAnyIp->isChecked())
            acceptConnections = 1;
        else
            acceptConnections = 0;
    Settings::set(Settings::ActiveRMAServer, Settings::AcceptAnyIP) = QVariant(acceptConnections);
    Settings::set(Settings::ActiveRMAServer, Settings::LogAccepted) = QVariant(ui->chkActiveRmaAcceptedConnections->isChecked()?1:0);
    Settings::set(Settings::ActiveRMAServer, Settings::LogRejected) = QVariant(ui->chkActiveRmaRejectedConnections->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
