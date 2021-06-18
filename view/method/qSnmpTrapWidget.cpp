#include "qSnmpTrapWidget.h"
#include "ui_qSnmpTrapWidget.h"
#include "qSnmpTrapFilterDlg.h"

namespace SDPO {

SnmpTrapWidget::SnmpTrapWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::SnmpTrapWidget)
{
    ui->setupUi(this);
    connect(ui->btnBadMessage, SIGNAL(clicked()), this, SLOT(onSnmpTrapFilterCall()));
    connect(ui->btnGoodMessage, SIGNAL(clicked()), this, SLOT(onSnmpTrapFilterCall()));
}

SnmpTrapWidget::~SnmpTrapWidget()
{
    delete ui;
}

void SnmpTrapWidget::onSnmpTrapFilterCall()
{
    SnmpTrapFilterDlg dlg;
    dlg.exec();
}

} // namespace SDPO
