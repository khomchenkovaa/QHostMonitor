#include "qTestPlannedPauseDlg.h"
#include "ui_qTestPlannedPauseDlg.h"

namespace SDPO {

TestPlannedPauseDlg::TestPlannedPauseDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestPlannedPauseDlg)
{
    ui->setupUi(this);
}

TestPlannedPauseDlg::~TestPlannedPauseDlg()
{
    delete ui;
}

} // namespace SDPO
