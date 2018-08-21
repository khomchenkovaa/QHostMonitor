#include "qLdapTestWidget.h"
#include "ui_qLdapTestWidget.h"

namespace SDPO {

LdapTestWidget::LdapTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::LdapTestWidget)
{
    ui->setupUi(this);
}

LdapTestWidget::~LdapTestWidget()
{
    delete ui;
}

} // namespace SDPO
