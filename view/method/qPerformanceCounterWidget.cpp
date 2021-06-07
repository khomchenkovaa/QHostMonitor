#include "qPerformanceCounterWidget.h"
#include "ui_qPerformanceCounterWidget.h"
#include "method/tPerformanceCounter.h"

namespace SDPO {

/******************************************************************/

PerformanceCounterWidget::PerformanceCounterWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::PerformanceCounterWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

PerformanceCounterWidget::~PerformanceCounterWidget()
{
    delete ui;
}
/******************************************************************/

void PerformanceCounterWidget::init(TestMethod *item)
{
    TPerformanceCounter *perfCounter = qobject_cast<TPerformanceCounter*>(item);
    ui->cmbCheckCounter->setCurrentText(perfCounter->getCheckCounter());
    ui->cmbAlert->setCurrentText(perfCounter->getAlertWhen());
    ui->spinAlert->setValue(perfCounter->getAlertWhenCounter());
    ui->cmbDisplayMode->setCurrentText(perfCounter->getDisplayMode());
    ui->chkConnect->setChecked(perfCounter->isConnectAs());
    ui->cmbDisplayMode->setCurrentText(perfCounter->getLogin());
    ui->lnConnectPassword->setText(perfCounter->getPassword());
}

/******************************************************************/

TestMethod *PerformanceCounterWidget::save(TestMethod *item)
{
    TPerformanceCounter* perfCounter;
    if (item && (item->getTMethodID() == TMethodID::PerfCounter)) {
        perfCounter = qobject_cast<TPerformanceCounter*>(item);
    } else {
        perfCounter = new TPerformanceCounter();
    }
    perfCounter->setCheckCounter(ui->cmbCheckCounter->currentText());
    perfCounter->setAlertWhen(ui->cmbAlert->currentText());
    perfCounter->setAlertWhenCounter(ui->spinAlert->value());
    perfCounter->setDisplayMode(ui->cmbDisplayMode->currentText());
    perfCounter->setConnectAs(ui->chkConnect->isChecked());
    perfCounter->setLogin(ui->cmbConnectLogin->currentText());
    perfCounter->setPassword(ui->lnConnectPassword->text());
    return perfCounter;
}

/******************************************************************/

void PerformanceCounterWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::PerfCounter);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbCheckCounter->clear();
    ui->cmbAlert->setCurrentText(QString("is < than"));
    ui->spinAlert->setValue(0.00);
    ui->cmbDisplayMode->setCurrentText(QString("as is"));
    ui->chkConnect->setChecked(false);
    ui->cmbConnectLogin->clear();
    ui->lnConnectPassword->clear();
}

/******************************************************************/

QStringList PerformanceCounterWidget::validate()
{
    QStringList errors;
    if(ui->cmbCheckCounter->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a performance counter"));
    }
    return errors;
}

/******************************************************************/

QString PerformanceCounterWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::PerfCounter);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::PerfCounter);
    case Macro::Path : return ui->cmbCheckCounter->currentText();
    case Macro::Object : return ui->cmbCheckCounter->currentText();
    case Macro::Object2 : return ui->spinAlert->text();
    case Macro::TestMode : return ui->cmbAlert->currentText();
    default: return QString();
    }

}

/******************************************************************/

} // namespace SDPO
