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

void ProxyOptionsWidget::init(QSettings *s)
{
    // Proxy server
    ui->editProxyServer->setText(s->value(SKEY_PROXY_Server,"127.0.0.1").toString());
    ui->spinProxyPort->setValue(s->value(SKEY_PROXY_Port,80).toInt());
    // Use proxy auth
    ui->boxProxyAuth->setChecked(s->value(SKEY_PROXY_Auth,1) == 1);
    ui->ProxyUserEdit->setText(s->value(SKEY_PROXY_User,"test").toString());
    ui->ProxyPswdEdit->setText(s->value(SKEY_PROXY_Pswd).toString());
    // Proxy bypass list
    ui->plainProxyBypassList->clear();
    ui->plainProxyBypassList->insertPlainText(s->value(SKEY_PROXY_Param2,"<local>;").toString());
}

/******************************************************************/

void ProxyOptionsWidget::prepareToSave(QSettings *s)
{
    // Proxy server
    s->setValue(SKEY_PROXY_Server,ui->editProxyServer->text());
    s->setValue(SKEY_PROXY_Port,ui->spinProxyPort->value());
    // Use proxy auth
    s->setValue(SKEY_PROXY_Auth,ui->boxProxyAuth->isChecked()?1:0);
    s->setValue(SKEY_PROXY_User,ui->ProxyUserEdit->text());
    s->setValue(SKEY_PROXY_Pswd,ui->ProxyPswdEdit->text());
    // Proxy bypass list
    s->setValue(SKEY_PROXY_Param2,ui->plainProxyBypassList->toPlainText());
}

/******************************************************************/

} // namespace SDPO
