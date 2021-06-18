#include "qTcpWidget.h"
#include "ui_qTcpWidget.h"

namespace SDPO {

TcpWidget::TcpWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::TcpWidget)
{
    ui->setupUi(this);
}

TcpWidget::~TcpWidget()
{
    delete ui;
}

} // namespace SDPO
