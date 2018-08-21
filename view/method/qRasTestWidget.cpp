#include "qRasTestWidget.h"
#include "ui_qRasTestWidget.h"

namespace SDPO {

RasTestWidget::RasTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::RasTestWidget)
{
    ui->setupUi(this);
}

RasTestWidget::~RasTestWidget()
{
    delete ui;
}

} // namespace SDPO
