#include "qSybaseWidget.h"
#include "ui_qSybaseWidget.h"

namespace SDPO {

SybaseWidget::SybaseWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::SybaseWidget)
{
    ui->setupUi(this);
}

SybaseWidget::~SybaseWidget()
{
    delete ui;
}

} // namespace SDPO {
