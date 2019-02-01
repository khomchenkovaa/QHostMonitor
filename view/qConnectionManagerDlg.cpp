#include "qConnectionManagerDlg.h"
#include "ui_qConnectionManagerDlg.h"

namespace SDPO {

ConnectionManagerDlg::ConnectionManagerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionManagerDlg)
{
    ui->setupUi(this);
}

ConnectionManagerDlg::~ConnectionManagerDlg()
{
    delete ui;
}

} //namespace SDPO
