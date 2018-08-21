#include "qSnmpTrapFilterDlg.h"
#include "ui_qSnmpTrapFilterDlg.h"

namespace SDPO {

SnmpTrapFilterDlg::SnmpTrapFilterDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnmpTrapFilterDlg)
{
    ui->setupUi(this);
}

SnmpTrapFilterDlg::~SnmpTrapFilterDlg()
{
    delete ui;
}

} // namespace SDPO
