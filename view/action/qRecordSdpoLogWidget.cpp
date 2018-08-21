#include "qRecordSdpoLogWidget.h"
#include "ui_qRecordSdpoLogWidget.h"
#include "action/tRecordSdpoLogAction.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

RecordSdpoLogWidget::RecordSdpoLogWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::RecordSdpoLogWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

RecordSdpoLogWidget::~RecordSdpoLogWidget()
{
    delete ui;
}

/******************************************************************/

void RecordSdpoLogWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::LogRecord) {
            return;
        }
        RecordSdpoLogAction *action = qobject_cast<RecordSdpoLogAction *>(item);
        ui->chkCommonLog->setChecked(action->isAddCommonLog());
        ui->chkPrivatLog->setChecked(action->isAddPrivateLog());
        ui->chkSpecificLog->setChecked(action->isAddSpecificLog());
        ui->editSpecificLog->setText(action->getSpecificLogFile());
}

/******************************************************************/

TestAction *RecordSdpoLogWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::LogRecord) {
        item = new RecordSdpoLogAction();
    }
    RecordSdpoLogAction *action = qobject_cast<RecordSdpoLogAction *>(item);
    action->setAddCommonLog(ui->chkCommonLog->isChecked());
    action->setAddPrivateLog(ui->chkPrivatLog->isChecked());
    action->setAddSpecificLog(ui->chkSpecificLog->isChecked());
    action->setSpecificLogFile(ui->editSpecificLog->text());
    return action;
}

/******************************************************************/

void RecordSdpoLogWidget::on_btnSpecificLog_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editSpecificLog->text());
    if (!fileName.isEmpty()) {
        ui->editSpecificLog->setText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO


