#include "qDnsTestWidget.h"
#include "ui_qDnsTestWidget.h"

namespace SDPO {

DnsTestWidget::DnsTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::DnsTestWidget)
{
    ui->setupUi(this);
}

DnsTestWidget::~DnsTestWidget()
{
    delete ui;
}

} // namespace SDPO
