#include "qAckDlg.h"
#include "ui_qAckDlg.h"

namespace SDPO {

/******************************************************************/

AckDlg::AckDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AckDlg)
{
    ui->setupUi(this);
    append = false;
    init();
}

/******************************************************************/

AckDlg::~AckDlg()
{
    delete ui;
}

/******************************************************************/

void AckDlg::init()
{
    ui->btnAck->setHidden(append);
    ui->btnAckAndStop->setHidden(append);
    ui->buttonBox->setHidden(append);
    ui->btnAppend->setHidden(!append);
    ui->btnCancel->setHidden(!append);
}

/******************************************************************/

} // namespace SDPO
