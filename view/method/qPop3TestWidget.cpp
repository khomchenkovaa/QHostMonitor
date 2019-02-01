#include "qPop3TestWidget.h"
#include "ui_qPop3TestWidget.h"

namespace SDPO {

Pop3TestWidget::Pop3TestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::Pop3TestWidget)
{
    ui->setupUi(this);
}

Pop3TestWidget::~Pop3TestWidget()
{
    delete ui;
}

} // namespace SDPO
