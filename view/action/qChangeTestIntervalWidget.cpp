#include "qChangeTestIntervalWidget.h"
#include "ui_qChangeTestIntervalWidget.h"
#include "action/tChangeTestIntervalAction.h"

namespace SDPO {

ChangeTestIntervalWidget::ChangeTestIntervalWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::ChangeTestIntervalWidget)
{
    ui->setupUi(this);
   // t=ui->timeSetToTime->time();
}

ChangeTestIntervalWidget::~ChangeTestIntervalWidget()
{
    delete ui;
}

void ChangeTestIntervalWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::TestInterval) {
        return;
    }
    ChangeTestIntervalAction *action = qobject_cast<ChangeTestIntervalAction *>(item);
    ui->rdRestoreOriginalValue->setChecked(action->isRestoreValue());
    ui->rdSetToTime->setChecked(action->isSetToTime());
    ui->timeSetToTime->setTime(action->getTimeValueSelect());
    ui->rdSetToValue->setChecked(action->isSetToPercent());
    ui->spinSetToValue->setValue(action->getPercent());
}

TestAction *ChangeTestIntervalWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::TestInterval) {
            item = new ChangeTestIntervalAction();
        }
    ChangeTestIntervalAction *action = qobject_cast<ChangeTestIntervalAction *>(item);
    action->setRestoreValue(ui->rdRestoreOriginalValue->isChecked());
    action->setSetToTime(ui->rdSetToTime->isChecked());
    action->setTimeValueSelect(ui->timeSetToTime->time());
    action->setSetToPercent(ui->rdSetToValue->isChecked());
    action->setPercent(ui->spinSetToValue->value());
    return action;
}

} // namespace SDPO
