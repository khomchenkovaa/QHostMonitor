#include "qLdapTestWidget.h"
#include "ui_qLdapTestWidget.h"
#include "method/tLdapTest.h"

namespace SDPO {

/*****************************************************************/

LdapTestWidget::LdapTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::LdapTestWidget)
{
    ui->setupUi(this);
    checkPerformSearch_clicked();
    connect(ui->chkPerformSearch, SIGNAL(clicked()),this, SLOT(checkPerformSearch_clicked()));
}

/*****************************************************************/

LdapTestWidget::~LdapTestWidget()
{
    delete ui;
}
/*****************************************************************/

void LdapTestWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Ldap) ) {
        reset();
        return;
    }
    TLdapTest* test = qobject_cast<TLdapTest*>(item);
    ui->cmbHost->setCurrentText(test->getHost());
    ui->spinPort->setValue(test->getPort());
    ui->spinTimeout->setValue(test->getTimeout());
    ui->lineLogin->setText(test->getLogin());
    ui->linePassword->setText(test->getPassword());
    ui->chkPerformSearch->setChecked(test->isCheckPerformSearch());
    ui->cmbBaseObject->setCurrentText(test->getBaseObject());
    ui->spinResLimit->setValue(test->getResLimit());
    ui->cmbSearchFilter->setCurrentText(test->getSearchFilter());
}

/*****************************************************************/

TTestMethod *LdapTestWidget::save(TTestMethod *item)
{
    TLdapTest* test;
    if (item && (item->getTMethodID() == TMethodID::Ldap)) {
        test = qobject_cast<TLdapTest*>(item);
    } else {
        test = new TLdapTest();
    }
    test->setHost(ui->cmbHost->currentText());
    test->setPort(ui->spinPort->value());
    test->setTimeout(ui->spinTimeout->value());
    test->setLogin(ui->lineLogin->text());
    test->setPassword(ui->linePassword->text());
    test->setCheckPerformSearch(ui->chkPerformSearch->isChecked());
    test->setBaseObject(ui->cmbBaseObject->currentText());
    test->setResLimit(ui->spinResLimit->value());
    test->setSearchFilter(ui->cmbSearchFilter->currentText());
    return test;
}

/******************************************************************/

void LdapTestWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::Ldap);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbHost->clear();
    ui->spinPort->setValue(389);
    ui->spinTimeout->setValue(60);
    ui->lineLogin->clear();
    ui->linePassword->clear();
    ui->chkPerformSearch->setChecked(false);
    ui->cmbBaseObject->clear();
    ui->spinResLimit->setValue(0);
    ui->cmbSearchFilter->clear();
}

/******************************************************************/

QStringList LdapTestWidget::validate()
{
    QStringList errors;
    if(ui->cmbHost->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a server"));
    }
    return errors;
}

/******************************************************************/

QString LdapTestWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Ldap);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::Ldap);
    case Macro::Host :return ui->cmbHost->currentText();
    case Macro::Object : return ui->cmbBaseObject->currentText();
    case Macro::TargetPort : return ui->spinPort->text();
    default: return QString();
    }
}

/*****************************************************************/

void LdapTestWidget::checkPerformSearch_clicked()
{
  if (ui->chkPerformSearch->isChecked())
    {
        ui->cmbBaseObject->setEnabled(true);
        ui->cmbSearchFilter->setEnabled(true);
        ui->spinResLimit->setEnabled(true);
    }
  else
    {
        ui->cmbBaseObject->setDisabled(true);
        ui->cmbSearchFilter->setDisabled(true);
        ui->spinResLimit->setDisabled(true);
    }
}

/******************************************************************/

} // namespace SDPO

