#include "qImapTestWidget.h"
#include "ui_qImapTestWidget.h"

namespace SDPO {

ImapTestWidget::ImapTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::ImapTestWidget)
{
    ui->setupUi(this);
}

ImapTestWidget::~ImapTestWidget()
{
    delete ui;
}

} // namespace SDPO
