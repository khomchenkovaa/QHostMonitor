#include "qMailRelayTestPropertiesDlg.h"
#include "ui_qMailRelayTestPropertiesDlg.h"

namespace SDPO {

MailRelayTestPropertiesDlg::MailRelayTestPropertiesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MailRelayTestPropertiesDlg)
{
    ui->setupUi(this);
}

MailRelayTestPropertiesDlg::~MailRelayTestPropertiesDlg()
{
    delete ui;
}

} // namespace SDPO
