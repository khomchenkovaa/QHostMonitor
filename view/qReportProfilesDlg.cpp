#include "qReportProfilesDlg.h"
#include "ui_qReportProfilesDlg.h"

namespace SDPO {

ReportProfilesDlg::ReportProfilesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportProfilesDlg)
{
    ui->setupUi(this);
}

ReportProfilesDlg::~ReportProfilesDlg()
{
    delete ui;
}

} // namespace SDPO
