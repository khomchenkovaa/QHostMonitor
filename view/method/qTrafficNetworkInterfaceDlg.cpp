#include "qTrafficNetworkInterfaceDlg.h"
#include "ui_qTrafficNetworkInterfaceDlg.h"

namespace SDPO {

TrafficNetworkInterfaceDlg::TrafficNetworkInterfaceDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrafficNetworkInterfaceDlg)
{
    ui->setupUi(this);
}

TrafficNetworkInterfaceDlg::~TrafficNetworkInterfaceDlg()
{
    delete ui;
}

} // namespace SDPO
