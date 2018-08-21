#include "qAccessMethodOptionsWidget.h"
#include "ui_qAccessMethodOptionsWidget.h"

namespace SDPO {

/******************************************************************/

AccessMethodOptionsWidget::AccessMethodOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::AccessMethodOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

AccessMethodOptionsWidget::~AccessMethodOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void AccessMethodOptionsWidget::on_btnAccessProxy_clicked()
{
    emit goToPage(5); //Proxy
}

/******************************************************************/

void AccessMethodOptionsWidget::init()
{
    QVariant value = Settings::get(Settings::HostMon, Settings::AccessMethod, QVariant(0));
            if (value.toInt() == 0)
                ui->rbAccessUseRegistry->setChecked(true);
            else if (value.toInt() == 1)
                ui->rbAccessDirect->setChecked(true);
            else if (value.toInt() == 2)
                ui->rbAccessViaProxy->setChecked(true);
            else if (value.toInt() == 3)
                ui->rbAccessPreconfig->setChecked(true);
       on_btnSelectAcessRetriveUrl();
       connect(ui->rbAccessUseRegistry, SIGNAL(clicked()),this, SLOT(on_btnSelectAcessRetriveUrl()));
       connect(ui->rbAccessDirect, SIGNAL(clicked()),this, SLOT(on_btnSelectAcessRetriveUrl()));
       connect(ui->rbAccessViaProxy, SIGNAL(clicked()),this, SLOT(on_btnSelectAcessRetriveUrl()));
       connect(ui->rbAccessPreconfig, SIGNAL(clicked()),this, SLOT(on_btnSelectAcessRetriveUrl()));

}

/******************************************************************/

void AccessMethodOptionsWidget::prepareToSave()
{
    int AccessMethods = 0;
            if (ui->rbAccessUseRegistry->isChecked()?1:0)
                AccessMethods = 0;
            else if (ui->rbAccessDirect->isChecked()?1:0)
                AccessMethods = 1;
            else if (ui->rbAccessViaProxy->isChecked()?1:0)
                AccessMethods = 2;
            else if (ui->rbAccessPreconfig->isChecked()?1:0)
                AccessMethods = 3;

   Settings::set(Settings::HostMon, Settings::AccessMethod) = QVariant(AccessMethods);
}

/******************************************************************/

void AccessMethodOptionsWidget::on_btnSelectAcessRetriveUrl()
{
    if(ui->rbAccessUseRegistry->isChecked())
    {
        ui->btnAccessProxy->setDisabled(true);
    }
    else if (ui->rbAccessDirect->isChecked())
    {
        ui->btnAccessProxy->setDisabled(true);
    }
    else if (ui->rbAccessViaProxy->isChecked())
    {
        ui->btnAccessProxy->setDisabled(false);
    }
    else if (ui->rbAccessPreconfig->isChecked())
    {
        ui->btnAccessProxy->setDisabled(true);
    }
}
/******************************************************************/

} // namespace SDPO

