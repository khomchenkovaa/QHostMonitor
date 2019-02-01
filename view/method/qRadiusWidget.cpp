#include "qRadiusWidget.h"
#include "ui_qRadiusWidget.h"

namespace SDPO {

RadiusWidget::RadiusWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::RadiusWidget)
{
    ui->setupUi(this);
}

RadiusWidget::~RadiusWidget()
{
    delete ui;
}

} // namespace SDPO
