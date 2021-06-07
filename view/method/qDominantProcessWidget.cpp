#include "qDominantProcessWidget.h"
#include "ui_qDominantProcessWidget.h"
#include "method/tDominantProcess.h"

namespace SDPO {

/*****************************************************************/

DominantProcessWidget::DominantProcessWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::DominantProcessWidget)
{
    ui->setupUi(this);
}

/*****************************************************************/

DominantProcessWidget::~DominantProcessWidget()
{
    delete ui;
}
/*****************************************************************/

void DominantProcessWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::DominantProcess) ) {
        reset();
        return;
    }
    TDominantProcess* test = qobject_cast<TDominantProcess*>(item);
    ui->cmbCheckProcesses->setCurrentText(test->getCheckProcessesOn());
    ui->lnExcludedProcesses->setText(test->getExcludeProcesses());
    ui->spinAlertIf->setValue(test->getAlertIfCount());
    ui->cmbAlertIf->setCurrentText(test->getAlertIf());
    ui->cmbTopProcess->setCurrentText(test->getTopProcesses());
    ui->chkConnectAs->setChecked(test->isConnectAs());
    ui->cmbConnectLogin->setCurrentText(test->getLogin());
    ui->lineConnectPassword->setText(test->getPassword());
}

/*****************************************************************/

TestMethod *DominantProcessWidget::save(TestMethod *item)
{
    TDominantProcess* test;
    if (item && (item->getTMethodID() == TMethodID::DominantProcess)) {
        test = qobject_cast<TDominantProcess*>(item);
    } else {
        test = new TDominantProcess();
    }
    test->setCheckProcessesOn(ui->cmbCheckProcesses->currentText());
    test->setExcludeProcesses(ui->lnExcludedProcesses->text());
    test->setAlertIfCount(ui->spinAlertIf->value());
    test->setAlertIf(ui->cmbAlertIf->currentText());
    test->setTopProcesses(ui->cmbTopProcess->currentText());
    test->setConnectAs(ui->chkConnectAs->isChecked());
    test->setLogin(ui->cmbConnectLogin->currentText());
    test->setPassword(ui->lineConnectPassword->text());
    return test;
}

/******************************************************************/

void DominantProcessWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::DominantProcess);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbCheckProcesses->setCurrentText(QString("localhost"));
    ui->lnExcludedProcesses->clear();
    ui->spinAlertIf->setValue(50);
    ui->cmbAlertIf->setCurrentText(QString("Memory (MB)"));
    ui->cmbTopProcess->setCurrentText(QString("value, process name, ID"));
    ui->chkConnectAs->setChecked(false);
    ui->cmbConnectLogin->clear();
    ui->lineConnectPassword->clear();
}

/******************************************************************/

QStringList DominantProcessWidget::validate()
{
    QStringList errors;
    return errors;
}

/******************************************************************/

QString DominantProcessWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::CPU);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::CPU);
    case Macro::Host : return ui->cmbCheckProcesses->currentText();
    case Macro::TestMode : return ui->cmbAlertIf->currentText();
    default: return QString();
    }
}

/******************************************************************/

} // namespace SDPO
