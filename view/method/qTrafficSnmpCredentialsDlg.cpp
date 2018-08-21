#include "qTrafficSnmpCredentialsDlg.h"
#include "ui_qTrafficSnmpCredentialsDlg.h"

namespace SDPO {

TrafficSnmpCredentialsDlg::TrafficSnmpCredentialsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrafficSnmpCredentialsDlg)
{
    ui->setupUi(this);
}

TrafficSnmpCredentialsDlg::~TrafficSnmpCredentialsDlg()
{
    delete ui;
}

} // namespace SDPO
