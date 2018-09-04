#include "qDnsTestWidget.h"
#include "ui_qDnsTestWidget.h"
#include "method/tDnsTest.h"

namespace SDPO {

/*****************************************************************/

DnsTestWidget::DnsTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::DnsTestWidget)
{
    ui->setupUi(this);
}

/*****************************************************************/

DnsTestWidget::~DnsTestWidget()
{
    delete ui;
}

/*****************************************************************/

void DnsTestWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::DNS) ) {
        reset();
        return;
    }
    TDnsTest* test = qobject_cast<TDnsTest*>(item);
    ui->cmbServer->setCurrentText(test->getServer());
    ui->spinTimeout->setValue(test->getTimeOut());
    ui->cmbProtocol->setCurrentText(test->getProtocol());
    ui->spinPort->setValue(test->getPort());
    ui->cmbRequest->setCurrentText(test->getRequest());
    ui->cmbRequestType->setCurrentText(test->getRequestType());
    ui->chkTestResultFor->setChecked(test->isTestResultFor());
    ui->cmbTestResultFor->setCurrentText(test->getTestResult());
}

/*****************************************************************/

TTestMethod *DnsTestWidget::save(TTestMethod *item)
{
    TDnsTest* test;
    if (item && (item->getTMethodID() == TMethodID::DNS)) {
        test = qobject_cast<TDnsTest*>(item);
    } else {
        test = new TDnsTest();
    }
    test->setServer(ui->cmbServer->currentText());
    test->setTimeOut(ui->spinTimeout->value());
    test->setProtocol(ui->cmbProtocol->currentText());
    test->setPort(ui->spinPort->value());
    test->setRequest(ui->cmbRequest->currentText());
    test->setRequestType(ui->cmbRequestType->currentText());
    test->setTestResultFor(ui->chkTestResultFor->isChecked());
    test->setTestResult(ui->cmbTestResultFor->currentText());
    return test;
}

/******************************************************************/

void DnsTestWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::DNS);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->spinTimeout->setValue(60);
    ui->cmbProtocol->setCurrentText(QString("UDP"));
    ui->spinPort->setValue(53);
    ui->cmbRequest->clear();
    ui->cmbRequestType->setCurrentText(QString("A"));
    ui->chkTestResultFor->setChecked(false);
    ui->cmbTestResultFor->clear();
}

/******************************************************************/

QStringList DnsTestWidget::validate()
{
    QStringList errors;
    return errors;
}

/******************************************************************/

QString DnsTestWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::DNS);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::DNS);
    case Macro::Host : return ui->cmbServer->currentText();
    case Macro::TestMode : return ui->cmbRequestType->currentText();
    default: return QString();
    }
}

/******************************************************************/

} // namespace SDPO
