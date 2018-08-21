#include "qMsSqlWidget.h"
#include "ui_qMsSqlWidget.h"

namespace SDPO {

MsSqlWidget::MsSqlWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::MsSqlWidget)
{
    ui->setupUi(this);
}

MsSqlWidget::~MsSqlWidget()
{
    delete ui;
}

} //namespace SDPO
