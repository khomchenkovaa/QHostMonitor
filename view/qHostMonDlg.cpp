#include "qHostMonDlg.h"
#include "ui_qHostMonDlg.h"

#include <QMessageBox>
#include <QDebug>

#include "method/qTestWidget.h"
#include "testedit/qAlertsEditWidget.h"
#include "testedit/qLogReportsEditWidget.h"
#include "testedit/qMasterTestsEditWidget.h"
#include "testedit/qExpressionTestsEditWidget.h"
#include "qMethodSelectDlg.h"
#include "qLinksList.h"
#include "qMacroEditorDlg.h"
#include "gSettings.h"
#include "tEnums.h"
#include "tTest.h"
#include "tRoot.h"
#include "global/gMacroTranslator.h"

namespace SDPO {

/******************************************************************/

HostMonDlg::HostMonDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostMonDlg),
    m_root(0),
    editItem(0)
{
    ui->setupUi(this);
    m_data = QVariant();
    changed = false;

    connect(ui->btnTestMethod, SIGNAL(clicked()), this, SLOT(openMethodSelectDialog()));
    connect(ui->btnTestMethodLabel, SIGNAL(clicked()), this, SLOT(openMethodSelectDialog()));
    connect(ui->stwTestMethod, SIGNAL(currentChanged(int)), this, SLOT(refreshName()));
    connect(ui->stwTestMethod, SIGNAL(currentChanged(int)), this, SLOT(refreshComment()));
    ui->cmbTestName->installEventFilter(this);
    ui->ledTestComment->installEventFilter(this);
    
    for (int i = 0; i < ui->stwTestMethod->count(); ++i) {
        TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->widget(i));
        if (widget) {
            connect(widget, SIGNAL(propertiesChanged()),this, SLOT(refreshName()));
            connect(widget, SIGNAL(propertiesChanged()),this, SLOT(refreshComment()));
        }
    }
    connect(ui->btnDependenciesHideLeft, SIGNAL(toggled(bool)), this, SLOT(hideDependencies(bool)));
    connect(ui->btnDependenciesHideRight, SIGNAL(toggled(bool)), this, SLOT(hideDependencies(bool)));
    connect(ui->btnStatusProcessingHide, SIGNAL(toggled(bool)), this, SLOT(hideOptional(bool)));
}

/******************************************************************/

HostMonDlg::~HostMonDlg()
{
    delete ui;
}

/******************************************************************/

void HostMonDlg::setRootNode(TNode *root)
{
    m_root = root;
}

/******************************************************************/

void HostMonDlg::on_btnOk_clicked()
{
    TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
    if (!widget) {
        QMessageBox::information(0,"Info", tr("Oops! Not implemented yet"));
        return;
    }
    QStringList errors = widget->validate();
    if (!errors.isEmpty()) {
        QMessageBox::warning(0,"Warning", errors.at(0));
        return;
    }
    TTestMethod* test;
    if (editItem) {
        test = editItem->method();
    } else {
        test = 0;
    }
    test = widget->save(test);
    test->setNamePattern(widget->getNamePattern());
    test->setCommentPattern(widget->getCommentPattern());
    saveTest(test);
    close();
}

/******************************************************************/

void HostMonDlg::reset()
{
    //main
    ui->cmbAgent->setCurrentIndex(0);
    ui->cmbTestName->clearEditText();
    ui->ledTestComment->clear();
    ui->cmbTestRelatedURL->clearEditText();

    // Schedule
    ui->btnScheduleRegular->setChecked(true);
    ui->btnScheduleIrregular->setChecked(false);
    ui->btnScheduleByExpression->setChecked(false);
    ui->stwSchedule->setCurrentIndex(1);
    ui->cmbSchedIrregularMode->setCurrentIndex(0);
    ui->cmbSchedDayOfMonth->setHidden(true);
    ui->cmbSchedDayOfWeek->setHidden(true);
    ui->sbScheduleHours->setValue(0);
    ui->sbScheduleMin->setValue(10);
    ui->sbScheduleSec->setValue(0);

    // Alerts
    AlertsEditWidget *alerts = qobject_cast<AlertsEditWidget*>(ui->grpAlerts);
    if (alerts) {
        alerts->reset();
    }

    // Log & reports
    LogReportsEditWidget *logReports = qobject_cast<LogReportsEditWidget*>(ui->grpLogsReports);
    if (logReports) {
        logReports->reset();
    }

    // Master tests
    ui->cmbDependencyMode->setCurrentIndex(0);
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->reset(m_root);
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->reset();
    }
    ui->chkSynchronizeCounters->setChecked(true);
    ui->chkSynchronizeStatusAlerts->setChecked(false);
    ui->treeDependentTests->clear();

    // Optional
    ui->chkReverseAlert->setChecked(false);
    ui->chkUnknownIsBad->setChecked(true);
    ui->chkWarningIsBad->setChecked(true);
    ui->chkUseWarningIf->setChecked(false);
    ui->chkUseNormalIf->setChecked(false);
    ui->chkTuneUpReply->setChecked(false);
    ui->cmbWarningCondition->setCurrentText(QString());
    ui->cmbNormalCondition->setCurrentText(QString());
    ui->cmbReply->setCurrentText(QString());
    ui->cmbEnabled->setCurrentIndex(0);
    ui->btnLinks->setVisible(false);

    for (int i=0; i<ui->stwTestMethod->count(); ++i) {
        TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->widget(i));
        if (widget) {
            widget->reset(m_data);
        }
    }
}

/******************************************************************/

void HostMonDlg::refreshName()
{
    ui->cmbTestName->setCurrentText(getTestName());
}

/******************************************************************/

void HostMonDlg::refreshComment()
{
    ui->ledTestComment->setText(getTestComment());
}

/******************************************************************/

void HostMonDlg::openMethodSelectDialog()
{
    MethodSelectDlg dlg;
    dlg.setCurrent(ui->cmbTestMethod->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        int idx = dlg.getCurrent();
        ui->cmbTestMethod->setCurrentIndex(idx);
    }
}

/******************************************************************/

void HostMonDlg::hideDependencies(bool hide)
{
    ui->btnDependenciesHideLeft->setChecked(hide);
    ui->btnDependenciesHideRight->setChecked(hide);
    if (ui->frmMasterTests->isHidden() != hide) {
        ui->frmMasterTests->setHidden(hide);
        ui->frmDependentTests->setHidden(hide);
        QSize newSize = size();
        int h = newSize.height();
        newSize.setHeight( hide ? h - ui->frmMasterTests->height() : h + ui->frmMasterTests->height() );
        qDebug() << "Size changed from:" << h << "to" << newSize.height();
        resize(newSize);
    }
}

/******************************************************************/

void HostMonDlg::hideOptional(bool hide)
{
    if (ui->frmOptional->isHidden() == hide) {
        return;
    }
    ui->btnStatusProcessingHide->setChecked(hide);
    ui->frmOptional->setHidden(hide);
    QSize newSize = size();
    int h = newSize.height();
    newSize.setHeight( hide ? h - ui->frmOptional->height() : h + ui->frmOptional->height() );
    qDebug() << "Size changed from:" << h << "to" << newSize.height();
    resize(newSize);
}

/******************************************************************/

void HostMonDlg::saveTest(TTestMethod *testMethod)
{
    QString testName = getTestName().trimmed();
    bool isNew = true;
    if (editItem) {
        isNew = false;
    } else {
        editItem = new TTest(TRoot::nextID(), testName);
    }

    editItem->setTest(testMethod);
    editItem->updateSpecificProperties();

    // main
    if (!testName.isEmpty())  {
        editItem->setName(testName);
        ui->cmbTestName->addItem(testName);
    }
    QString taskComment = getTestComment().trimmed();
    if (!taskComment.isEmpty()) editItem->setComment(taskComment);
    QString relatedUrl = ui->cmbTestRelatedURL->currentText().trimmed();
    if (!relatedUrl.isEmpty()) {
        editItem->setRelatedURL(relatedUrl);
        ui->cmbTestRelatedURL->addItem(relatedUrl);
    }
    // schedule
    if (ui->btnScheduleRegular->isChecked()) {
        editItem->setRegularSchedule((ui->sbScheduleHours->value() * 60 +
                      ui->sbScheduleMin->value()) * 60 +
                      ui->sbScheduleSec->value(),
                      ui->cmbSchedule->currentText());
    } else if (ui->btnScheduleIrregular->isChecked()) {
        int idx = ui->cmbSchedIrregularMode->currentIndex();
        int schedDay = 0;
        if (idx == 1) schedDay = ui->cmbSchedDayOfWeek->currentIndex();
        else if (idx == 2) schedDay = ui->cmbSchedDayOfMonth->currentIndex();
        editItem->setIrregularSchedule(
                    idx,schedDay,
                    ui->timeSchedIrregular->time()
                    );
    } else if (ui->btnScheduleByExpression->isChecked()) {
        editItem->setByExpressionSchedule(
                    ui->cmbScheduleExpr1->currentText(),
                    ui->cmbScheduleExpr2->currentText());
    }

    // alerts
    AlertsEditWidget *alerts = qobject_cast<AlertsEditWidget*>(ui->grpAlerts);
    if (alerts) {
        alerts->save(editItem);
    }

    // Log & reports
    LogReportsEditWidget *logReports = qobject_cast<LogReportsEditWidget*>(ui->grpLogsReports);
    if (logReports) {
        logReports->save(editItem);
    }

    // Master tests
    editItem->setDependencyMode(ui->cmbDependencyMode->currentIndex());
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->save(editItem);
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->save(editItem);
    }
    editItem->setSynchronizeCounters(ui->chkSynchronizeCounters->isChecked());
    editItem->setSynchronizeStatusAlerts(ui->chkSynchronizeStatusAlerts->isChecked());

    // optional
    editItem->setReverseAlert(ui->chkReverseAlert->isChecked());
    editItem->setUnknownIsBad(ui->chkUnknownIsBad->isChecked());
    editItem->setWarningIsBad(ui->chkWarningIsBad->isChecked());
    editItem->setUseWarningScript(ui->chkUseWarningIf->isChecked());
    editItem->setUseNormalScript(ui->chkUseNormalIf->isChecked());
    editItem->setTuneUpReply(ui->chkTuneUpReply->isChecked());
    editItem->setWarningScript(ui->cmbWarningCondition->currentText());
    editItem->setNormalScript(ui->cmbNormalCondition->currentText());
    editItem->setTuneUpScript(ui->cmbReply->currentText());
    editItem->setEnabled(ui->cmbEnabled->currentIndex() == 0);    

    if (isNew) {
        emit testAdded(editItem);
    } else {
        emit testChanged(editItem);
    }
}

/******************************************************************/

QString HostMonDlg::getTestName() const
{
    TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
    QString nameSource = widget->getNamePattern();
    GMacroTranslator translator(nameSource);
    QStringList nameParams = translator.parse();
    if (nameParams.count()) {
        QMap<QString,QString> nameValues = widget->setTemplateVars(nameParams);
        translator.setValues(nameValues);
        return translator.build();
    }
    return nameSource;
}

/******************************************************************/

QString HostMonDlg::getTestComment() const
{
    TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
    QString commentSource = widget->getCommentPattern();
    GMacroTranslator translator(commentSource);
    QStringList commentParams = translator.parse();
    if (commentParams.count()) {
        QMap<QString,QString> commentValues = widget->setTemplateVars(commentParams);
        translator.setValues(commentValues);
        return translator.build();
    }
    return commentSource;
}

/******************************************************************/

bool HostMonDlg::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
         if (watched == ui->cmbTestName) {
             TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
             QString nameSource = widget->getNamePattern();
             ui->cmbTestName->setCurrentText(nameSource);
             GMacroTranslator translator(nameSource);
             QStringList nameParams = translator.parse();
             if (nameParams.count()) {
                 QPalette palette = ui->cmbTestName->palette();
                 palette.setColor(QPalette::Base,Qt::yellow);
                 ui->cmbTestName->setPalette(palette);
             }
         } else if (watched == ui->ledTestComment) {
             TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
             QString commentSource = widget->getCommentPattern();
             ui->ledTestComment->setText(commentSource);
             GMacroTranslator translator(commentSource);
             QStringList commentParams = translator.parse();
             if (commentParams.count()) {
                 QPalette palette = ui->ledTestComment->palette();
                 palette.setColor(QPalette::Base,Qt::yellow);
                 ui->ledTestComment->setPalette(palette);
             }
         }
    }
    if (event->type() == QEvent::FocusOut) {
        if (watched == ui->cmbTestName) {
            TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
            widget->setNamePattern(ui->cmbTestName->currentText());
            refreshName();
            QPalette palette = ui->cmbTestName->palette();
            palette.setColor(QPalette::Base,Qt::white);
            ui->cmbTestName->setPalette(palette);
        } else if (watched == ui->ledTestComment) {
            TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
            widget->setCommentPattern(ui->ledTestComment->text());
            refreshComment();
            QPalette palette = ui->ledTestComment->palette();
            palette.setColor(QPalette::Base,Qt::white);
            ui->ledTestComment->setPalette(palette);
        }
    }
    return QDialog::eventFilter(watched,event);
}

/******************************************************************/

void HostMonDlg::init(TTest *item)
{
    editItem = item;
    if(!editItem) {
        init(TMethodID::Ping);
        return;
    }
    // main
    ui->cmbTestMethod->setCurrentIndex(editItem->testMethodId());
    ui->cmbTestName->setCurrentText(editItem->testName());
    ui->ledTestComment->setText(editItem->getComment());
    ui->cmbTestRelatedURL->setCurrentText(editItem->getRelatedURL());

    // schedule
    int hours = editItem->interval()/(60*60); // hours
    int min = (editItem->interval() - hours*60*60) / 60; // minutes
    int sec = (editItem->interval() - hours*60*60 - min*60); // sec
    switch( editItem->scheduleMode() ) {
    case 0: // Regular
        on_btnScheduleRegular_clicked();
        ui->sbScheduleHours->setValue(hours);
        ui->sbScheduleMin->setValue(min);
        ui->sbScheduleSec->setValue(sec);
        ui->cmbSchedule->setCurrentText(editItem->scheduleName());
        break;
    case 1: // Irregular - OneTestPerDay
        on_btnScheduleIrregular_clicked();
        ui->cmbSchedIrregularMode->setCurrentIndex(0);
        on_cmbSchedIrregularMode_currentIndexChanged(0);
        ui->timeSchedIrregular->setTime(editItem->scheduleTime());
        break;
    case 2: // Irregular - OneTestPerWeek
        on_btnScheduleIrregular_clicked();
        ui->cmbSchedIrregularMode->setCurrentIndex(1);
        on_cmbSchedIrregularMode_currentIndexChanged(1);
        ui->cmbSchedDayOfWeek->setCurrentIndex(editItem->scheduleDay());
        ui->timeSchedIrregular->setTime(editItem->scheduleTime());
        break;
    case 3: // Irregular - OneTestPerMonth
        on_btnScheduleIrregular_clicked();
        ui->cmbSchedIrregularMode->setCurrentIndex(2);
        on_cmbSchedIrregularMode_currentIndexChanged(2);
        ui->cmbSchedDayOfMonth->setCurrentIndex(editItem->scheduleDay());
        ui->timeSchedIrregular->setTime(editItem->scheduleTime());
        break;
    case 4: // By Expression
        on_btnScheduleByExpression_clicked();
        ui->cmbScheduleExpr1->setCurrentText(editItem->scheduleExpr1());
        ui->cmbScheduleExpr2->setCurrentText(editItem->scheduleExpr2());
        break;
    }

    // alerts
    AlertsEditWidget *alerts = qobject_cast<AlertsEditWidget*>(ui->grpAlerts);
    if (alerts) {
        alerts->init(editItem);
    }

    // Log & reports
    LogReportsEditWidget *logReports = qobject_cast<LogReportsEditWidget*>(ui->grpLogsReports);
    if (logReports) {
        logReports->init(editItem);
    }

    // Master tests
    ui->cmbDependencyMode->setCurrentIndex(editItem->getDependencyMode());
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->init(editItem);
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->init(editItem);
    }
    ui->chkSynchronizeCounters->setChecked(editItem->isSynchronizeCounters());
    ui->chkSynchronizeStatusAlerts->setChecked(editItem->isSynchronizeStatusAlerts());
    ui->treeDependentTests->clear(); //! TODO

    // optional
    ui->cmbEnabled->setCurrentIndex(editItem->isEnabled()?0:1);
    ui->chkReverseAlert->setChecked(editItem->isReverseAlert());
    ui->chkUnknownIsBad->setChecked(editItem->isUnknownIsBad());
    ui->chkWarningIsBad->setChecked(editItem->isWarningIsBad());
    ui->chkUseWarningIf->setChecked(editItem->isUseWarningScript());
    ui->chkUseNormalIf->setChecked(editItem->isUseNormalScript());
    ui->chkTuneUpReply->setChecked(editItem->isTuneUpReply());
    ui->cmbWarningCondition->setCurrentText(editItem->getWarningScript());
    ui->cmbNormalCondition->setCurrentText(editItem->getNormalScript());
    ui->cmbReply->setCurrentText(editItem->getTuneUpScript());
    ui->btnLinks->setVisible(editItem->linkCount() > 0);

    emit ui->cmbTestMethod->currentIndexChanged(ui->cmbTestMethod->currentIndex());

    TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
    if (widget) {
        widget->init(editItem->method());
        widget->setNamePattern(editItem->method()->getNamePattern());
        widget->setCommentPattern(editItem->method()->getCommentPattern());
        refreshName();
        refreshComment();
    }
}

/******************************************************************/

void HostMonDlg::init(TMethodID method, QVariant data)
{
    editItem = 0;
    m_data = data;
    reset();
    ui->cmbTestMethod->setCurrentIndex((int)method);
    emit ui->cmbTestMethod->currentIndexChanged(ui->cmbTestMethod->currentIndex());
}

/******************************************************************/

void HostMonDlg::on_btnLinks_clicked()
{
    if (!editItem) return;
    if (editItem->linkCount() == 0) return;

    LinksList linksDlg(editItem);
    linksDlg.setReadOnly();
    linksDlg.exec();
}

/******************************************************************/

void HostMonDlg::on_btnScheduleRegular_clicked()
{
    ui->btnScheduleRegular->setChecked(true);
    ui->btnScheduleIrregular->setChecked(false);
    ui->btnScheduleByExpression->setChecked(false);
    ui->stwSchedule->setCurrentIndex(1);
}

/******************************************************************/

void HostMonDlg::on_btnScheduleIrregular_clicked()
{
    ui->btnScheduleRegular->setChecked(false);
    ui->btnScheduleIrregular->setChecked(true);
    ui->btnScheduleByExpression->setChecked(false);
    ui->stwSchedule->setCurrentIndex(2);
}

/******************************************************************/

void HostMonDlg::on_btnScheduleByExpression_clicked()
{
    ui->btnScheduleRegular->setChecked(false);
    ui->btnScheduleIrregular->setChecked(false);
    ui->btnScheduleByExpression->setChecked(true);
    ui->stwSchedule->setCurrentIndex(0);
}

/******************************************************************/

void HostMonDlg::on_cmbSchedIrregularMode_currentIndexChanged(int index)
{
    switch(index) {
    case 0: // once a day
        ui->cmbSchedDayOfMonth->setHidden(true);
        ui->cmbSchedDayOfWeek->setHidden(true);
        break;
    case 1: // once a week
        ui->cmbSchedDayOfMonth->setHidden(true);
        ui->cmbSchedDayOfWeek->setHidden(false);
        break;
    case 2: // once a month
        ui->cmbSchedDayOfMonth->setHidden(false);
        ui->cmbSchedDayOfWeek->setHidden(true);
        break;
    }
}

/******************************************************************/

void HostMonDlg::on_btnSchedulesDlg_clicked()
{
    qDebug() << "TODO: HostMonDlg -> OpenSchedilesDlg";
}

/******************************************************************/

void HostMonDlg::on_btnWarningCondition_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Use 'Warning' status if"));
    dlg.setScript(ui->cmbWarningCondition->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbWarningCondition->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void HostMonDlg::on_btnNormalCondition_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Use 'Normal' status if"));
    dlg.setScript(ui->cmbNormalCondition->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbNormalCondition->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void HostMonDlg::on_btnTuneUpReply_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Tune up reply"));
    dlg.setScript(ui->cmbReply->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbReply->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

} // namespace SDPO
