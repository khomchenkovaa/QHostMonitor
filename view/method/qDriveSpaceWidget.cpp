#include "qDriveSpaceWidget.h"
#include "ui_qDriveSpaceWidget.h"

namespace SDPO {

DriveSpaceWidget::DriveSpaceWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::DriveSpaceWidget)
{
    ui->setupUi(this);
}

DriveSpaceWidget::~DriveSpaceWidget()
{
    delete ui;
}

} // namespace SDPO
