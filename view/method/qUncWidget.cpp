#include "qUncWidget.h"
#include "ui_qUncWidget.h"

namespace SDPO {

UncWidget::UncWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::UncWidget)
{
    ui->setupUi(this);
}

UncWidget::~UncWidget()
{
    delete ui;
}

} //namespace SDPO
