#include "qAboutDlg.h"
#include "ui_qAboutDlg.h"

namespace SDPO {

/******************************************************************/

AboutDlg::AboutDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDlg)
{
    ui->setupUi(this);
}

/******************************************************************/

AboutDlg::~AboutDlg()
{
    delete ui;
}

} // namespace SDPO
