#include "qNtpTestWidget.h"
#include "ui_qNtpTestWidget.h"
#include "method/tNtpTest.h"

namespace SDPO {

/******************************************************************/

NtpTestWidget::NtpTestWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::NtpTestWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

NtpTestWidget::~NtpTestWidget()
{
    delete ui;
}

/******************************************************************/

void NtpTestWidget::init(TestMethod *item)
{
    TNtpTest *ntpTest = qobject_cast<TNtpTest*>(item);
    ui->cmbServer->setCurrentText(ntpTest->getServer());
    ui->spinPort->setValue(ntpTest->getPort());
    ui->spinRetries->setValue(ntpTest->getRetries());
    ui->spinTimeout->setValue(ntpTest->getTimeout());
    ui->chkAlertDifference->setChecked(ntpTest->isAlertWhen());
    ui->spinAlertDifference->setValue(ntpTest->getSec());
    ui->cmbDisplayMode->setCurrentText(ntpTest->getDisplayMode());
}

/******************************************************************/

TestMethod *NtpTestWidget::save(TestMethod *item)
{
    TNtpTest* ntpTest;
    if (item && (item->getTMethodID() == TMethodID::NTP)) {
        ntpTest = qobject_cast<TNtpTest*>(item);
    } else {
        ntpTest = new TNtpTest();
    }
    ntpTest->setServer(ui->cmbServer->currentText());
    ntpTest->setPort(ui->spinPort->value());
    ntpTest->setRetries(ui->spinRetries->value());
    ntpTest->setTimeout(ui->spinTimeout->value());
    ntpTest->setAlertWhen(ui->chkAlertDifference->isChecked());
    ntpTest->setSec(ui->spinAlertDifference->value());
    ntpTest->setDisplayMode(ui->cmbDisplayMode->currentText());
    return ntpTest;
}

/******************************************************************/

void NtpTestWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::NTP);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->spinPort->setValue(123);
    ui->spinRetries->setValue(3);
    ui->spinTimeout->setValue(5);
    ui->chkAlertDifference->setChecked(false);
    ui->spinAlertDifference->setValue(10);
    ui->cmbDisplayMode->setCurrentText(QString("Reply time"));
}

/******************************************************************/

QStringList NtpTestWidget::validate()
{
    QStringList errors;
    if(ui->cmbServer->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a server"));
    }
    return errors;
}

/******************************************************************/

QString NtpTestWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::NTP);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::NTP);
    case Macro::Host : return ui->cmbServer->currentText();
    case Macro::Path : return ui->spinPort->text();

    default: return QString();
    }

}

/******************************************************************/

} // namespace SDPO
