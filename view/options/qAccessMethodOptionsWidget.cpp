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

void AccessMethodOptionsWidget::init(QSettings *s)
{
    switch(s->value(SKEY_HOSTMON_AccessMethod, 0).toInt()) {
        case 0: ui->rbAccessUseRegistry->setChecked(true); break;
        case 1: ui->rbAccessDirect->setChecked(true); break;
        case 2: ui->rbAccessViaProxy->setChecked(true); break;
        case 3: ui->rbAccessPreconfig->setChecked(true); break;
    }
    on_btnSelectAcessRetriveUrl();
    connect(ui->rbAccessUseRegistry, SIGNAL(clicked()),this, SLOT(on_btnSelectAcessRetriveUrl()));
    connect(ui->rbAccessDirect, SIGNAL(clicked()),this, SLOT(on_btnSelectAcessRetriveUrl()));
    connect(ui->rbAccessViaProxy, SIGNAL(clicked()),this, SLOT(on_btnSelectAcessRetriveUrl()));
    connect(ui->rbAccessPreconfig, SIGNAL(clicked()),this, SLOT(on_btnSelectAcessRetriveUrl()));
}

/******************************************************************/

void AccessMethodOptionsWidget::prepareToSave(QSettings *s)
{
    int idx = 0;
    if (ui->rbAccessUseRegistry->isChecked())
        idx = 0;
    else if (ui->rbAccessDirect->isChecked())
        idx = 1;
    else if (ui->rbAccessViaProxy->isChecked())
        idx = 2;
    else if (ui->rbAccessPreconfig->isChecked())
        idx = 3;
    s->setValue(SKEY_HOSTMON_AccessMethod, idx);
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

