#include "qHttpWidget.h"
#include "ui_qHttpWidget.h"
#include "qHttpTestPropertiesDlg.h"
#include "qHttpProxiesListDlg.h"

namespace SDPO {

HttpWidget::HttpWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::HttpWidget)
{
    ui->setupUi(this);
}

HttpWidget::~HttpWidget()
{
    delete ui;
}

void HttpWidget::on_btnAdvanced_clicked()
{
    HttpTestPropertiesDlg dlg;
    dlg.exec();
}

void HttpWidget::on_btnProxy_clicked()
{
    HttpProxiesListDlg dlg;
    dlg.exec();
}

} // namespace SDPO




