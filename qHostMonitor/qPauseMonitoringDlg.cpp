#include "qPauseMonitoringDlg.h"
#include "ui_qPauseMonitoringDlg.h"

namespace SDPO {

PauseMonitoringDlg::PauseMonitoringDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseMonitoringDlg)
{
    ui->setupUi(this);
}

PauseMonitoringDlg::~PauseMonitoringDlg()
{
    delete ui;
}

} // namespace SDPO
