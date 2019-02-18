#include "qPop3TestWidget.h"
#include "ui_qPop3TestWidget.h"
#include "method/tPop3Test.h"

namespace SDPO {

/******************************************************************/

Pop3TestWidget::Pop3TestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::Pop3TestWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

Pop3TestWidget::~Pop3TestWidget()
{
    delete ui;
}

/******************************************************************/

void Pop3TestWidget::init(TTestMethod *item)
{
    TPop3Test *perfCounter = qobject_cast<TPop3Test*>(item);
    ui->cmbServer->setCurrentText(perfCounter->getServer());
    ui->spinPort->setValue(perfCounter->getPort());
    ui->cmbLogin->setCurrentText(perfCounter->getLogin());
    ui->cmbTLS->setCurrentText(perfCounter->getTLS());
    ui->lnPassword->setText(perfCounter->getPassword());
    ui->spinTimeout->setValue(perfCounter->getTimeout());
    ui->ChkAlertMessage->setChecked(perfCounter->isAlertMessage());
    ui->spinAlertMessage->setValue(perfCounter->getMessages());
    ui->chkAlertSize->setChecked(perfCounter->isAlertSize());
    ui->spinAlertSize->setValue(perfCounter->getSize());
}

/******************************************************************/

TTestMethod *Pop3TestWidget::save(TTestMethod *item)
{
    TPop3Test* perfCounter;
    if (item && (item->getTMethodID() == TMethodID::PerfCounter)) {
        perfCounter = qobject_cast<TPop3Test*>(item);
    } else {
        perfCounter = new TPop3Test();
    }
    perfCounter->setServer(ui->cmbServer->currentText());
    perfCounter->setPort(ui->spinPort->value());
    perfCounter->setLogin(ui->cmbLogin->currentText());
    perfCounter->setTLS(ui->cmbTLS->currentText());
    perfCounter->setPassword(ui->lnPassword->text());
    perfCounter->setTimeout(ui->spinPort->value());
    perfCounter->setAlertMessage(ui->ChkAlertMessage->isChecked());
    perfCounter->setMessages(ui->spinAlertMessage->value());
    perfCounter->setAlertSize(ui->chkAlertSize->isChecked());
    perfCounter->setSize(ui->spinAlertSize->value());
    return perfCounter;
}

/******************************************************************/

void Pop3TestWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::POP3);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->spinPort->setValue(110);
    ui->cmbLogin->clear();
    ui->cmbTLS->setCurrentText(QString("none"));
    ui->lnPassword->clear();
    ui->spinPort->setValue(60);
    ui->ChkAlertMessage->setChecked(false);
    ui->spinAlertMessage->setValue(100);
    ui->chkAlertSize->setChecked(false);
    ui->spinAlertSize->setValue(50);
}

/******************************************************************/

QStringList Pop3TestWidget::validate()
{
    QStringList errors;
    if(ui->cmbServer->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a server"));
    }
    return errors;
}

/******************************************************************/

QString Pop3TestWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::PerfCounter);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::PerfCounter);
    case Macro::Host : return ui->cmbServer->currentText();
    case Macro::Object : return ui->cmbLogin->currentText();
    case Macro::TargetPort : return ui->spinPort->text();
    default: return QString();
}

}
/******************************************************************/

} // namespace SDPO
