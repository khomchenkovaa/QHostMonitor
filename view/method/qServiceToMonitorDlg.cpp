#include "qServiceToMonitorDlg.h"
#include "ui_qServiceToMonitorDlg.h"

namespace SDPO {

ServiceToMonitorDlg::ServiceToMonitorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServiceToMonitorDlg)
{
    ui->setupUi(this);
}

ServiceToMonitorDlg::~ServiceToMonitorDlg()
{
    delete ui;
}

} // namespace SDPO
