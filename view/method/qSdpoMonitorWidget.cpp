#include "qSdpoMonitorWidget.h"
#include "ui_qSdpoMonitorWidget.h"

namespace SDPO {

SdpoMonitorWidget::SdpoMonitorWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::SdpoMonitorWidget)
{
    ui->setupUi(this);
}

SdpoMonitorWidget::~SdpoMonitorWidget()
{
    delete ui;
}

} // namespace SDPO
