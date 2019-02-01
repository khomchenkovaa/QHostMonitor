#include "qImapTestWidget.h"
#include "ui_qImapTestWidget.h"
#include "method/tImapTest.h"

namespace SDPO {

/*****************************************************************/

ImapTestWidget::ImapTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::ImapTestWidget)
{
    ui->setupUi(this);
    checkMail_clicked();
    connect(ui->chkMail, SIGNAL(clicked()),this, SLOT(checkMail_clicked()));
}

/*****************************************************************/

ImapTestWidget::~ImapTestWidget()
{
    delete ui;
}

/*****************************************************************/

void ImapTestWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::IMAP) ) {
        reset();
        return;
    }
    TImapTest* test = qobject_cast<TImapTest*>(item);
    ui->cmbServer->setCurrentText(test->getServer());
    ui->spinPort->setValue(test->getPort());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->cmbTLS->setCurrentText(test->getTls());
    ui->lnPassword->setText(test->getPassword());
    ui->spinTimeout->setValue(test->getTimeout());
    ui->chkMail->setChecked(test->isCheckMailbox());
    ui->cmbMessageFolder->setCurrentText(test->getMessageFolder());
    ui->cmbMessageStatus->setCurrentText(test->getMessageStatus());
    ui->cmbMessageAlert->setCurrentText(test->getMessageAlert());;
    ui->spinMessageSize->setValue(test->getMessageSize());
}

/*****************************************************************/

TTestMethod *ImapTestWidget::save(TTestMethod *item)
{
    TImapTest* test;
    if (item && (item->getTMethodID() == TMethodID::IMAP)) {
        test = qobject_cast<TImapTest*>(item);
    } else {
        test = new TImapTest();
    }
    test->setServer(ui->cmbServer->currentText());
    test->setPort(ui->spinPort->value());
    test->setLogin(ui->cmbLogin->currentText());
    test->setTls(ui->cmbTLS->currentText());
    test->setPassword(ui->lnPassword->text());
    test->setTimeout(ui->spinTimeout->value());
    test->setCheckMailbox(ui->chkMail->isChecked());
    test->setMessageFolder(ui->cmbMessageFolder->currentText());
    test->setMessageStatus(ui->cmbMessageStatus->currentText());
    test->setMessageAlert(ui->cmbMessageAlert->currentText());
    test->setMessageSize(ui->spinMessageSize->value());
    return test;
}

/******************************************************************/

void ImapTestWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::IMAP);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->spinPort->setValue(143);
    ui->cmbLogin->clear();
    ui->cmbTLS->setCurrentText(QString("none"));
    ui->lnPassword->clear();
    ui->spinTimeout->setValue(60);
    ui->chkMail->setChecked(false);
    ui->cmbMessageFolder->setCurrentText(QString("Inbox"));
    ui->cmbTLS->setCurrentText(QString("All messages"));
    ui->cmbMessageAlert->setCurrentText(QString("Allert when size of all messages bigger than"));
    ui->spinMessageSize->setValue(0);
}

/******************************************************************/

QStringList ImapTestWidget::validate()
{
    QStringList errors;
    if(ui->cmbServer->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a server"));
    }
    return errors;
}

/******************************************************************/

QString ImapTestWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::IMAP);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::IMAP);
    case Macro::Host :return ui->cmbServer->currentText();
    case Macro::Object : return ui->cmbLogin->currentText();
    case Macro::TargetPort : return ui->spinPort->text();
    default: return QString();
    }
}

/*****************************************************************/

void ImapTestWidget::checkMail_clicked()
{
  if (ui->chkMail->isChecked())
    {
        ui->cmbMessageFolder->setEnabled(true);
        ui->cmbMessageStatus->setEnabled(true);
        ui->cmbMessageAlert->setEnabled(true);
        ui->spinMessageSize->setEnabled(true);
    }
  else
    {
        ui->cmbMessageFolder->setDisabled(true);
        ui->cmbMessageStatus->setDisabled(true);
        ui->cmbMessageAlert->setDisabled(true);
        ui->spinMessageSize->setDisabled(true);
    }
}

/******************************************************************/

} // namespace SDPO
