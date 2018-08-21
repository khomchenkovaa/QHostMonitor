#include "qWmiWidget.h"
#include "ui_qWmiWidget.h"

namespace SDPO {

WmiWidget::WmiWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::WmiWidget)
{
    ui->setupUi(this);
}

WmiWidget::~WmiWidget()
{
    delete ui;
}

} // namespace SDPO
