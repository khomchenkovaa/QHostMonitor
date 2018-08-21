#include "qTestInfoDlg.h"
#include "ui_qTestInfoDlg.h"
#include "qTestHistoryChartsDlg.h"

namespace SDPO {

TestInfoDlg::TestInfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestInfoDlg)
{
    ui->setupUi(this);
}

TestInfoDlg::~TestInfoDlg()
{
    delete ui;
}

void TestInfoDlg::on_btnTestHistory_clicked()
{
    TestHistoryChartsDlg dlg;
    dlg.exec();
}

} // namespace SDPO


