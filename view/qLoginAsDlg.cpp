#include "qLoginAsDlg.h"
#include "ui_qLoginAsDlg.h"

namespace SDPO {

LoginAsDlg::LoginAsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginAsDlg)
{
    ui->setupUi(this);
}

LoginAsDlg::~LoginAsDlg()
{
    delete ui;
}

} // namespace SDPO
