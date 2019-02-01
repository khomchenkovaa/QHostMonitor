#include "qHttpTestPropertiesDlg.h"
#include "ui_qHttpTestPropertiesDlg.h"
#include "qHttpProxiesListDlg.h"

namespace SDPO {

HttpTestPropertiesDlg::HttpTestPropertiesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HttpTestPropertiesDlg)
{
    ui->setupUi(this);
}

HttpTestPropertiesDlg::~HttpTestPropertiesDlg()
{
    delete ui;
}

void HttpTestPropertiesDlg::on_btnProxy_clicked()
{
    HttpProxiesListDlg dlg;
    dlg.exec();
}

} // namespace SDPO


