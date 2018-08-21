#include "qMailRelayWidget.h"
#include "ui_qMailRelayWidget.h"
#include "qMailRelayTestPropertiesDlg.h"

namespace SDPO {

MailRelayWidget::MailRelayWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::MailRelayWidget)
{
    ui->setupUi(this);
    connect(ui->btnIncoming, SIGNAL(clicked()), this, SLOT(openPropertiesDlg()));
    connect(ui->btnOutgoing, SIGNAL(clicked()), this, SLOT(openPropertiesDlg()));
    connect(ui->btnSender, SIGNAL(clicked()), this, SLOT(openPropertiesDlg()));
}

MailRelayWidget::~MailRelayWidget()
{
    delete ui;
}

void MailRelayWidget::openPropertiesDlg()
{
    MailRelayTestPropertiesDlg dlg(this);
    dlg.exec();
}

} // namespace SDPO
