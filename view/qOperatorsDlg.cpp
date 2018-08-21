#include "qOperatorsDlg.h"
#include "ui_qOperatorsDlg.h"

namespace SDPO {

OperatorsDlg::OperatorsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperatorsDlg)
{
    ui->setupUi(this);
}

OperatorsDlg::~OperatorsDlg()
{
    delete ui;
}

} // namespace SDPO
