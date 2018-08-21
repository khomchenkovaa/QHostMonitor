#include "qNtEventLogWidget.h"
#include "ui_qNtEventLogWidget.h"

namespace SDPO {

NtEventLogWidget::NtEventLogWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::NtEventLogWidget)
{
    ui->setupUi(this);
}

NtEventLogWidget::~NtEventLogWidget()
{
    delete ui;
}

} // namespace SDPO
