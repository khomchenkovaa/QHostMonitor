#include "qUrlTestPropertiesDlg.h"
#include "ui_qUrlTestPropertiesDlg.h"
namespace SDPO {

UrlTestPropertiesDlg::UrlTestPropertiesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UrlTestPropertiesDlg)
{
    ui->setupUi(this);
}

UrlTestPropertiesDlg::~UrlTestPropertiesDlg()
{
    delete ui;
}

} // namespace SDPO
