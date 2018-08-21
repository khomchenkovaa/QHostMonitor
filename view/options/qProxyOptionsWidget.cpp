#include "qProxyOptionsWidget.h"
#include "ui_qProxyOptionsWidget.h"

namespace SDPO {

ProxyOptionsWidget::ProxyOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::ProxyOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

ProxyOptionsWidget::~ProxyOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void ProxyOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::HostMon, Settings::ProxyServer, QVariant("127.0.0.1"));
        ui->editProxyServer->setText(value.toString());

    value = Settings::get(Settings::HostMon, Settings::ProxyPort, QVariant(80));
        ui->spinProxyPort->setValue(value.toInt());

    value = Settings::get(Settings::HostMon, Settings::ProxyAut, QVariant(1));
        if (value.toInt() == 1)
            ui->boxProxyAuth->setChecked(true);
        else
            ui->boxProxyAuth->setChecked(false);

    value = Settings::get(Settings::HostMon, Settings::ProxyUser, QVariant("test"));
        ui->ProxyUserEdit->setText(value.toString());

    value = Settings::get(Settings::HostMon, Settings::ProxyPswd, QVariant(""));
        ui->ProxyPswdEdit->setText(value.toString());

    value = Settings::get(Settings::HostMon, Settings::ProxyParam2, QVariant("<local>;"));
        ui->plainProxyBypassList->clear();
        ui->plainProxyBypassList->insertPlainText(value.toString());
}

/******************************************************************/

void ProxyOptionsWidget::prepareToSave()
{
    Settings::set(Settings::HostMon, Settings::ProxyServer) = QVariant(ui->editProxyServer->text());
    Settings::set(Settings::HostMon, Settings::ProxyPort) = QVariant(ui->spinProxyPort->value());
    Settings::set(Settings::HostMon, Settings::ProxyAut) = QVariant(ui->boxProxyAuth->isChecked()?1:0);
    Settings::set(Settings::HostMon, Settings::ProxyUser) = QVariant(ui->ProxyUserEdit->text());
    Settings::set(Settings::HostMon, Settings::ProxyPswd) = QVariant(ui->ProxyPswdEdit->text());
    Settings::set(Settings::HostMon, Settings::ProxyParam2) = QVariant(ui->plainProxyBypassList->toPlainText());

    
}

/******************************************************************/

} // namespace SDPO
