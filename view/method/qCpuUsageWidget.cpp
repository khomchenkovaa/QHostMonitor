#include "qCpuUsageWidget.h"
#include "ui_qCpuUsageWidget.h"
#include "method/tCpuUsage.h"

namespace SDPO {

/*****************************************************************/

CpuUsageWidget::CpuUsageWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::CpuUsageWidget)
{
    ui->setupUi(this);
    connect(ui->cmbCpuComputer, SIGNAL(currentTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/*****************************************************************/

CpuUsageWidget::~CpuUsageWidget()
{
    delete ui;
}

/*****************************************************************/

void CpuUsageWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::CPU) ) {
        reset();
        return;
    }
    TCpuUsage* test = qobject_cast<TCpuUsage*>(item);
    ui->cmbCpuComputer->setCurrentText(test->getComputer());
    ui->cmbCpuOs->setCurrentText(test->getOsSelect());
    ui->spinAlertWhen->setValue(test->getAlertWhen());
    ui->chkCpuConnect->setChecked(test->isConnectAs());
    ui->cmbCpuUser->setCurrentText(test->getLogin());
    ui->lineCpuPassword->setText(test->getPassword());
}

/*****************************************************************/

TTestMethod *CpuUsageWidget::save(TTestMethod *item)
{
    TCpuUsage* test;
    if (item && (item->getTMethodID() == TMethodID::CPU)) {
        test = qobject_cast<TCpuUsage*>(item);
    } else {
        test = new TCpuUsage();
    }
    test->setComputer(ui->cmbCpuComputer->currentText());
    test->setOsSelect(ui->cmbCpuOs->currentText());
    test->setAlertWhen(ui->spinAlertWhen->value());
    test->setConnectAs(ui->chkCpuConnect->isChecked());
    test->setLogin(ui->cmbCpuUser->currentText());
    test->setPassword(ui->lineCpuPassword->text());
    return test;
}

/******************************************************************/

void CpuUsageWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::CPU);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbCpuComputer->setCurrentText(QString("localhost"));
    on_ComputerSelect();
    connect(ui->cmbCpuComputer, SIGNAL(editTextChanged(QString)), this, SLOT(on_ComputerSelect()));

    ui->cmbCpuOs->setCurrentText(QString("Linux"));
    ui->spinAlertWhen->setValue(50);
    ui->chkCpuConnect->setChecked(false);
    ui->cmbCpuUser->setCurrentText(QString("UserName"));
    ui->lineCpuPassword->clear();
}

/******************************************************************/

QStringList CpuUsageWidget::validate()
{
    QStringList errors;
    return errors;
}

/******************************************************************/

QString CpuUsageWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::CPU);
    case Macro::TestMethod : return TMethod::toName(TMethodID::CPU);
    case Macro::Host : return ui->cmbCpuComputer->currentText();
    default: return QString();
    }
}

/******************************************************************/

void CpuUsageWidget::on_ComputerSelect()
{
    QString ComputerName = ui->cmbCpuComputer->currentText();
    if (ComputerName == "localhost")
    {
        ui->cmbCpuOs->setDisabled(true);
        ui->chkCpuConnect->setDisabled(true);
        ui->cmbCpuUser->setDisabled(true);
        ui->lineCpuPassword->setDisabled(true);
    }
    else
    {
        ui->cmbCpuOs->setEnabled(true);
        ui->chkCpuConnect->setEnabled(true);
        ui->cmbCpuUser->setEnabled(true);
        ui->lineCpuPassword->setEnabled(true);
    }
}

/******************************************************************/

} // namespace SDPO
