#include "qTestHistoryChartsDlg.h"
#include "ui_qTestHistoryChartsDlg.h"

namespace SDPO {

TestHistoryChartsDlg::TestHistoryChartsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestHistoryChartsDlg)
{
    ui->setupUi(this);
}

TestHistoryChartsDlg::~TestHistoryChartsDlg()
{
    delete ui;
}

} // namespace SDPO
