#include "qSshWidget.h"
#include "ui_qSshWidget.h"

namespace SDPO {

SshWidget::SshWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::SshWidget)
{
  ui->setupUi(this);
}

SshWidget::~SshWidget()
{
  delete ui;
}

} // namespace SDPO
