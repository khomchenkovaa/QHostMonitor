#include "qUdpTestWidget.h"
#include "ui_qUdpTestWidget.h"

namespace SDPO {

UdpTestWidget::UdpTestWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::UdpTestWidget)
{
    ui->setupUi(this);
}

UdpTestWidget::~UdpTestWidget()
{
    delete ui;
}

} // namespace SDPO
