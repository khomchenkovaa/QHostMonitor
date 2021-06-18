#include "qSmtpTestWidget.h"
#include "ui_qSmtpTestWidget.h"

namespace SDPO {

SmtpTestWidget::SmtpTestWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::SmtpTestWidget)
{
    ui->setupUi(this);
}

SmtpTestWidget::~SmtpTestWidget()
{
    delete ui;
}

} // namespace SDPO
