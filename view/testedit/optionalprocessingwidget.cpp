#include "optionalprocessingwidget.h"
#include "ui_optionalprocessingwidget.h"

#include "tTest.h"
#include "qMacroEditorDlg.h"

#include <QDebug>

using namespace SDPO;

/******************************************************************/

OptionalProcessingWidget::OptionalProcessingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionalProcessingWidget)
{
    ui->setupUi(this);
    setupUI();
}

/******************************************************************/

OptionalProcessingWidget::~OptionalProcessingWidget()
{
    delete ui;
}

/******************************************************************/

void OptionalProcessingWidget::reset()
{
    ui->chkReverseAlert->setChecked(false);
    ui->chkUnknownIsBad->setChecked(true);
    ui->chkWarningIsBad->setChecked(true);
    ui->chkUseWarningIf->setChecked(false);
    ui->chkUseNormalIf->setChecked(false);
    ui->chkTuneUpReply->setChecked(false);
    ui->cmbWarningCondition->setCurrentText(QString());
    ui->cmbNormalCondition->setCurrentText(QString());
    ui->cmbReply->setCurrentText(QString());
}

/******************************************************************/

void OptionalProcessingWidget::init(TTest *item)
{
    ui->chkReverseAlert->setChecked(item->isReverseAlert());
    ui->chkUnknownIsBad->setChecked(item->isUnknownIsBad());
    ui->chkWarningIsBad->setChecked(item->isWarningIsBad());
    ui->chkUseWarningIf->setChecked(item->isUseWarningScript());
    ui->chkUseNormalIf->setChecked(item->isUseNormalScript());
    ui->chkTuneUpReply->setChecked(item->isTuneUpReply());
    ui->cmbWarningCondition->setCurrentText(item->getWarningScript());
    ui->cmbNormalCondition->setCurrentText(item->getNormalScript());
    ui->cmbReply->setCurrentText(item->getTuneUpScript());
}

/******************************************************************/

void OptionalProcessingWidget::save(TTest *item)
{
    item->setReverseAlert(ui->chkReverseAlert->isChecked());
    item->setUnknownIsBad(ui->chkUnknownIsBad->isChecked());
    item->setWarningIsBad(ui->chkWarningIsBad->isChecked());
    item->setUseWarningScript(ui->chkUseWarningIf->isChecked());
    item->setUseNormalScript(ui->chkUseNormalIf->isChecked());
    item->setTuneUpReply(ui->chkTuneUpReply->isChecked());
    item->setWarningScript(ui->cmbWarningCondition->currentText());
    item->setNormalScript(ui->cmbNormalCondition->currentText());
    item->setTuneUpScript(ui->cmbReply->currentText());
}

/******************************************************************/

void OptionalProcessingWidget::hideOptional(bool hide)
{
    if (ui->frmOptional->isHidden() == hide) {
        return;
    }
    ui->btnStatusProcessingHide->setChecked(hide);
    ui->frmOptional->setHidden(hide);
}

/******************************************************************/

void OptionalProcessingWidget::onBtnWarningCondition()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Use 'Warning' status if"));
    dlg.setScript(ui->cmbWarningCondition->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbWarningCondition->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void OptionalProcessingWidget::onBtnNormalCondition()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Use 'Normal' status if"));
    dlg.setScript(ui->cmbNormalCondition->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbNormalCondition->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void OptionalProcessingWidget::onBtnTuneUpReply()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Tune up reply"));
    dlg.setScript(ui->cmbReply->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbReply->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

void OptionalProcessingWidget::setupUI()
{
    connect(ui->btnTuneUpReply, &QToolButton::clicked,
            this, &OptionalProcessingWidget::onBtnTuneUpReply);
    connect(ui->btnWarningCondition, &QToolButton::clicked,
            this, &OptionalProcessingWidget::onBtnWarningCondition);
    connect(ui->btnNormalCondition, &QToolButton::clicked,
            this, &OptionalProcessingWidget::onBtnNormalCondition);
    connect(ui->btnStatusProcessingHide, &QPushButton::toggled,
            this, &OptionalProcessingWidget::hideOptional);
}

/******************************************************************/
