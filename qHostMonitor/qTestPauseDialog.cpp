#include "qTestPauseDialog.h"
#include "ui_qTestPauseDialog.h"

namespace SDPO {

TestPauseDialog::TestPauseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestPauseDialog)
{
    ui->setupUi(this);
}

TestPauseDialog::~TestPauseDialog()
{
    delete ui;
}

} // namespace SDPO
