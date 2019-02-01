#include "qDynamicViewReportsWidget.h"
#include "ui_qDynamicViewReportsWidget.h"

namespace SDPO {

DynamicViewReportsWidget::DynamicViewReportsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicViewReportsWidget)
{
    ui->setupUi(this);
}

DynamicViewReportsWidget::~DynamicViewReportsWidget()
{
    delete ui;
}

} // namespace SDPO
