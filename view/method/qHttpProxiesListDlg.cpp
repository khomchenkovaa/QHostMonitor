#include "qHttpProxiesListDlg.h"
#include "ui_qHttpProxiesListDlg.h"

namespace SDPO {

HttpProxiesListDlg::HttpProxiesListDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HttpProxiesListDlg)
{
    ui->setupUi(this);
}

HttpProxiesListDlg::~HttpProxiesListDlg()
{
    delete ui;
}

} // namespace SDPO
