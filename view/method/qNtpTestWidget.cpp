#include "qNtpTestWidget.h"
#include "ui_qNtpTestWidget.h"

namespace SDPO {

NtpTestWidget::NtpTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::NtpTestWidget)
{
    ui->setupUi(this);
}

NtpTestWidget::~NtpTestWidget()
{
    delete ui;
}

} // namespace SDPO
