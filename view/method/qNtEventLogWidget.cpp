#include "qNtEventLogWidget.h"
#include "ui_qNtEventLogWidget.h"
#include "method/tNtEventLog.h"
#include "QMessageBox"
namespace SDPO {

/*****************************************************************/

NtEventLogWidget::NtEventLogWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::NtEventLogWidget)
{
    ui->setupUi(this);
    on_btnLogSource_clicked();
    connect(ui->btnLogSource,SIGNAL(clicked()),this,SLOT(on_btnLogSource_clicked()));
    on_btnAlertCondition_clicked();
    connect(ui->btnAlertCondition,SIGNAL(clicked()),this,SLOT(on_btnAlertCondition_clicked()));
    on_btnConnectAs_clicked();
    connect(ui->btnConnectAs,SIGNAL(clicked()),this,SLOT(on_btnConnectAs_clicked()));
}

/*****************************************************************/

NtEventLogWidget::~NtEventLogWidget()
{
    delete ui;
}

/*****************************************************************/

void NtEventLogWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::NTLog) ) {
        reset();
        return;
    }
    TNtEventLog* test = qobject_cast<TNtEventLog*>(item);
    ui->btnLogSource->setChecked(test->isLogSource());
    ui->btnAlertCondition->setChecked(test->isAlertCondition());
    ui->btnConnectAs->setChecked(test->isConnectAs());
    ui->cmbCompatibility->setCurrentText(test->getCompatibility());
    ui->cmbComputer->setCurrentText(test->getComputerUnc());
    ui->cmbLog->setCurrentText(test->getLog());
    ui->cmbEventSource->setCurrentText(test->getEventSource());
    ui->editComputer->setText(test->getComputer());
    ui->editEventType->setText(test->getEventType());
    ui->editEventId->setText(test->getEventId());
    ui->editDescription->setText(test->getDescription());
    ui->chkConnectToRemote->setChecked(test->isConnectToRemote());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->editPassword->setText(test->getPassword());
}

/*****************************************************************/

TestMethod *NtEventLogWidget::save(TestMethod *item)
{
    TNtEventLog* test;
    if (item && (item->getTMethodID() == TMethodID::NTLog)) {
        test = qobject_cast<TNtEventLog*>(item);
    } else {
        test = new TNtEventLog();
    }
    test->setLogSource(ui->btnLogSource->isChecked());
    test->setAlertCondition(ui->btnAlertCondition->isChecked());
    test->setConnectAs(ui->btnConnectAs->isChecked());
    test->setCompatibility(ui->cmbCompatibility->currentText());
    test->setComputerUnc(ui->cmbComputer->currentText());
    test->setLog(ui->cmbLog->currentText());
    test->setEventSource(ui->cmbEventSource->currentText());
    test->setComputer(ui->editComputer->text());
    test->setEventType(ui->editEventType->text());
    test->setEventId(ui->editEventId->text());
    test->setDescription(ui->editDescription->text());
    test->setConnectToRemote(ui->chkConnectToRemote->isChecked());
    test->setLogin(ui->cmbLogin->currentText());
    test->setPassword(ui->editPassword->text());
    return test;
}

/******************************************************************/

void NtEventLogWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::NTLog);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->btnLogSource->setChecked(true);
    on_btnLogSource_clicked();
    ui->btnAlertCondition->setChecked(false);
    ui->btnConnectAs->setChecked(false);
    ui->cmbCompatibility->setCurrentText(QString("Linux"));
    ui->cmbComputer->setCurrentText(QString("localhost"));
    ui->cmbLog->setCurrentText(QString(""));
    ui->cmbEventSource->setCurrentText(QString(""));
    ui->editComputer->setText(QString("Any"));
    ui->editEventType->setText(QString("Any"));
    ui->editEventId->setText(QString("Any"));
    ui->editDescription->setText(QString("Any"));
    ui->chkConnectToRemote->setChecked(false);
    ui->cmbLogin->setCurrentText(QString(""));
    ui->editPassword->setText(QString(""));
}

/******************************************************************/

QStringList NtEventLogWidget::validate()
{
    QStringList errors;
    return errors;
}

/******************************************************************/

QString NtEventLogWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::NTLog);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::NTLog);
    case Macro::Host : return ui->cmbComputer->currentText();
    case Macro::Path : return ui->cmbLog->currentText();
    case Macro::Object : return ui->cmbEventSource->currentText();
    default: return QString();
    }
}

/******************************************************************/

void NtEventLogWidget::on_btnLogSource_clicked()

{
    ui->btnLogSource->setDown(true);
    ui->btnAlertCondition->setDown(false);
    ui->btnConnectAs->setDown(false);
    ui->Event->setCurrentIndex(2);
}

/******************************************************************/

void NtEventLogWidget::on_btnAlertCondition_clicked()

{
    ui->btnLogSource->setDown(false);
    ui->btnAlertCondition->setDown(true);
    ui->btnConnectAs->setDown(false);
    ui->Event->setCurrentIndex(1);
}

/******************************************************************/

void NtEventLogWidget::on_btnConnectAs_clicked()

{
    ui->btnLogSource->setDown(false);
    ui->btnAlertCondition->setDown(false);
    ui->btnConnectAs->setDown(true);
    ui->Event->setCurrentIndex(0);
}

/******************************************************************/

} // namespace SDPO
