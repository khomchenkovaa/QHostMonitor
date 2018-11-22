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
#include "hmListService.h"
#include "global/gMacroTranslator.h"

namespace SDPO {

/******************************************************************/

HostMonDlg::HostMonDlg(HMListService *hml, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostMonDlg),
    m_HML(hml),
    m_Item(0)
{
    ui->setupUi(this);
    m_Data = QVariant();
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
    if (m_Item) {
        test = m_Item->method();
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
        masterTests->reset(m_HML->rootFolder());
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
            widget->reset(m_Data);
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
    if (m_Item) {
        isNew = false;
    } else {
        m_Item = new TTest(m_HML->nextID(), testName);
    }

    m_Item->setMethod(testMethod);
    m_Item->updateSpecificProperties();

    // main
    if (!testName.isEmpty())  {
        m_Item->setName(testName);
        ui->cmbTestName->addItem(testName);
    }
    QString taskComment = getTestComment().trimmed();
    if (!taskComment.isEmpty()) m_Item->setComment(taskComment);
    QString relatedUrl = ui->cmbTestRelatedURL->currentText().trimmed();
    if (!relatedUrl.isEmpty()) {
        m_Item->setRelatedURL(relatedUrl);
        ui->cmbTestRelatedURL->addItem(relatedUrl);
    }
    // schedule
    if (ui->btnScheduleRegular->isChecked()) {
        m_Item->setRegularSchedule((ui->sbScheduleHours->value() * 60 +
                      ui->sbScheduleMin->value()) * 60 +
                      ui->sbScheduleSec->value(),
                      ui->cmbSchedule->currentText());
    } else if (ui->btnScheduleIrregular->isChecked()) {
        switch (ui->cmbSchedIrregularMode->currentIndex()) {
        case 0: // once per day
            m_Item->setOncePerDaySchedule(ui->timeSchedIrregular->time());
            break;
        case 1: // once per week
            m_Item->setOncePerWeekSchedule(ui->cmbSchedDayOfWeek->currentIndex(), ui->timeSchedIrregular->time());
            break;
        case 2: // once per month
            m_Item->setOncePerMonthSchedule(ui->cmbSchedDayOfMonth->currentIndex(), ui->timeSchedIrregular->time());
            break;
        }
    } else if (ui->btnScheduleByExpression->isChecked()) {
        m_Item->setByExpressionSchedule(
                    ui->cmbScheduleExpr1->currentText(),
                    ui->cmbScheduleExpr2->currentText());
    }

    // alerts
    AlertsEditWidget *alerts = qobject_cast<AlertsEditWidget*>(ui->grpAlerts);
    if (alerts) {
        alerts->save(m_Item);
    }

    // Log & reports
    LogReportsEditWidget *logReports = qobject_cast<LogReportsEditWidget*>(ui->grpLogsReports);
    if (logReports) {
        logReports->save(m_Item);
    }

    // Master tests
    m_Item->setDependencyMode(ui->cmbDependencyMode->currentIndex());
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->save(m_Item);
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->save(m_Item);
    }
    m_Item->setSynchronizeCounters(ui->chkSynchronizeCounters->isChecked());
    m_Item->setSynchronizeStatusAlerts(ui->chkSynchronizeStatusAlerts->isChecked());

    // optional
    m_Item->setReverseAlert(ui->chkReverseAlert->isChecked());
    m_Item->setUnknownIsBad(ui->chkUnknownIsBad->isChecked());
    m_Item->setWarningIsBad(ui->chkWarningIsBad->isChecked());
    m_Item->setUseWarningScript(ui->chkUseWarningIf->isChecked());
    m_Item->setUseNormalScript(ui->chkUseNormalIf->isChecked());
    m_Item->setTuneUpReply(ui->chkTuneUpReply->isChecked());
    m_Item->setWarningScript(ui->cmbWarningCondition->currentText());
    m_Item->setNormalScript(ui->cmbNormalCondition->currentText());
    m_Item->setTuneUpScript(ui->cmbReply->currentText());
    m_Item->setEnabled(ui->cmbEnabled->currentIndex() == 0);

    if (isNew) {
        m_HML->addNode(m_HML->currentFolder(),m_Item);
        // emit testAdded(m_Item);
    } else {
        emit testChanged(m_Item);
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
    m_Item = item;
    if(!m_Item) {
        init(TMethodID::Ping);
        return;
    }
    // main
    ui->cmbTestMethod->setCurrentIndex(m_Item->testMethodId());
    ui->cmbTestName->setCurrentText(m_Item->testName());
    ui->ledTestComment->setText(m_Item->getComment());
    ui->cmbTestRelatedURL->setCurrentText(m_Item->getRelatedURL());

    // schedule
    int hours = m_Item->interval()/(60*60); // hours
    int min = (m_Item->interval() - hours*60*60) / 60; // minutes
    int sec = (m_Item->interval() - hours*60*60 - min*60); // sec
    switch( m_Item->schedule()->getMode() ) {
    case TSchedule::Regular : // Regular
        on_btnScheduleRegular_clicked();
        ui->sbScheduleHours->setValue(hours);
        ui->sbScheduleMin->setValue(min);
        ui->sbScheduleSec->setValue(sec);
        ui->cmbSchedule->setCurrentText(m_Item->schedule()->getScheduleName());
        break;
    case TSchedule::OncePerDay : // Irregular - OneTestPerDay
        on_btnScheduleIrregular_clicked();
        ui->cmbSchedIrregularMode->setCurrentIndex(0);
        on_cmbSchedIrregularMode_currentIndexChanged(0);
        ui->timeSchedIrregular->setTime(m_Item->schedule()->getScheduleTime());
        break;
    case TSchedule::OncePerWeek : // Irregular - OneTestPerWeek
        on_btnScheduleIrregular_clicked();
        ui->cmbSchedIrregularMode->setCurrentIndex(1);
        on_cmbSchedIrregularMode_currentIndexChanged(1);
        ui->cmbSchedDayOfWeek->setCurrentIndex(m_Item->schedule()->getScheduleDay());
        ui->timeSchedIrregular->setTime(m_Item->schedule()->getScheduleTime());
        break;
    case TSchedule::OncePerMonth : // Irregular - OneTestPerMonth
        on_btnScheduleIrregular_clicked();
        ui->cmbSchedIrregularMode->setCurrentIndex(2);
        on_cmbSchedIrregularMode_currentIndexChanged(2);
        ui->cmbSchedDayOfMonth->setCurrentIndex(m_Item->schedule()->getScheduleDay());
        ui->timeSchedIrregular->setTime(m_Item->schedule()->getScheduleTime());
        break;
    case TSchedule::ByExpression : // By Expression
        on_btnScheduleByExpression_clicked();
        ui->cmbScheduleExpr1->setCurrentText(m_Item->schedule()->getScheduleExpr1());
        ui->cmbScheduleExpr2->setCurrentText(m_Item->schedule()->getScheduleExpr2());
        break;
    }

    // alerts
    AlertsEditWidget *alerts = qobject_cast<AlertsEditWidget*>(ui->grpAlerts);
    if (alerts) {
        alerts->init(m_Item);
    }

    // Log & reports
    LogReportsEditWidget *logReports = qobject_cast<LogReportsEditWidget*>(ui->grpLogsReports);
    if (logReports) {
        logReports->init(m_Item);
    }

    // Master tests
    ui->cmbDependencyMode->setCurrentIndex(m_Item->getDependencyMode());
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->init(m_Item);
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->init(m_Item);
    }
    ui->chkSynchronizeCounters->setChecked(m_Item->isSynchronizeCounters());
    ui->chkSynchronizeStatusAlerts->setChecked(m_Item->isSynchronizeStatusAlerts());
    ui->treeDependentTests->clear(); //! TODO

    // optional
    ui->cmbEnabled->setCurrentIndex(m_Item->isEnabled()?0:1);
    ui->chkReverseAlert->setChecked(m_Item->isReverseAlert());
    ui->chkUnknownIsBad->setChecked(m_Item->isUnknownIsBad());
    ui->chkWarningIsBad->setChecked(m_Item->isWarningIsBad());
    ui->chkUseWarningIf->setChecked(m_Item->isUseWarningScript());
    ui->chkUseNormalIf->setChecked(m_Item->isUseNormalScript());
    ui->chkTuneUpReply->setChecked(m_Item->isTuneUpReply());
    ui->cmbWarningCondition->setCurrentText(m_Item->getWarningScript());
    ui->cmbNormalCondition->setCurrentText(m_Item->getNormalScript());
    ui->cmbReply->setCurrentText(m_Item->getTuneUpScript());
    ui->btnLinks->setVisible(m_Item->linkCount() > 0);

    emit ui->cmbTestMethod->currentIndexChanged(ui->cmbTestMethod->currentIndex());

    TestWidget* widget = qobject_cast<TestWidget*>(ui->stwTestMethod->currentWidget());
    if (widget) {
        widget->init(m_Item->method());
        widget->setNamePattern(m_Item->method()->getNamePattern());
        widget->setCommentPattern(m_Item->method()->getCommentPattern());
        refreshName();
        refreshComment();
    }
}

/******************************************************************/

void HostMonDlg::init(TMethodID method, QVariant data)
{
    m_Item = 0;
    m_Data = data;
    reset();
    ui->cmbTestMethod->setCurrentIndex((int)method);
    emit ui->cmbTestMethod->currentIndexChanged(ui->cmbTestMethod->currentIndex());
}

/******************************************************************/

void HostMonDlg::on_btnLinks_clicked()
{
    if (!m_Item) return;
    if (m_Item->linkCount() == 0) return;

    LinksList linksDlg(m_Item);
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
