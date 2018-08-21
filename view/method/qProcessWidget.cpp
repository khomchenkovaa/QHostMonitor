#include "qProcessWidget.h"
#include "ui_qProcessWidget.h"

namespace SDPO {

ProcessWidget::ProcessWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::ProcessWidget)
{
    ui->setupUi(this);
}

ProcessWidget::~ProcessWidget()
{
    delete ui;
}

} // namespace SDPO
