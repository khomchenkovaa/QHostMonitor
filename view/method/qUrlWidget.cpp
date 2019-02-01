#include "qUrlWidget.h"
#include "ui_qUrlWidget.h"
#include "qUrlTestPropertiesDlg.h"

namespace SDPO {

UrlWidget::UrlWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::UrlWidget)
{
    ui->setupUi(this);
}

UrlWidget::~UrlWidget()
{
    delete ui;
}

void SDPO::UrlWidget::on_btnUrl_clicked()
{
    UrlTestPropertiesDlg dlg;
    dlg.exec();
}

void SDPO::UrlWidget::on_btnAdvanced_clicked()
{
    UrlTestPropertiesDlg dlg;
    dlg.exec();
}

} // namespace SDPO


