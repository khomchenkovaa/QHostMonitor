#include "qServiceWidget.h"
#include "ui_qServiceWidget.h"
#include "qServiceToMonitorDlg.h"

namespace SDPO {

/******************************************************************/

ServiceWidget::ServiceWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::ServiceWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

ServiceWidget::~ServiceWidget()
{
    delete ui;
}

/******************************************************************/

void SDPO::ServiceWidget::on_btnServiceToMonitor_clicked()
{
    ServiceToMonitorDlg dlg;
    dlg.exec();
}

/******************************************************************/

} // namespace SDPO

