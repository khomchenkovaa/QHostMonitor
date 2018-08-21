#include "qDominantProcessWidget.h"
#include "ui_qDominantProcessWidget.h"

namespace SDPO {

DominantProcessWidget::DominantProcessWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::DominantProcessWidget)
{
    ui->setupUi(this);
}

DominantProcessWidget::~DominantProcessWidget()
{
    delete ui;
}

} // namespace SDPO
