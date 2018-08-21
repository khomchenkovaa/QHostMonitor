#include "qTraceTestWidget.h"
#include "ui_qTraceTestWidget.h"

namespace SDPO {

TraceTestWidget::TraceTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::TraceTestWidget)
{
    ui->setupUi(this);
}

TraceTestWidget::~TraceTestWidget()
{
    delete ui;
}

} // namespace SDPO
