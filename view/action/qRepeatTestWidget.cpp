#include "qRepeatTestWidget.h"
#include "ui_qRepeatTestWidget.h"
#include "action/tRepeatTestAction.h"

namespace SDPO {

/******************************************************************/

RepeatTestWidget::RepeatTestWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::RepeatTestWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

RepeatTestWidget::~RepeatTestWidget()
{
    delete ui;
}

/******************************************************************/

void RepeatTestWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::TestRepeat) {
        return;
    }
    RepeatTestAction *action = qobject_cast<RepeatTestAction *>(item);
        ui->rdRepeatTest->setChecked(action->isRepeatTest());
        ui->rdRecheckTest->setChecked(action->isRecheckTest());
}

/******************************************************************/

TestAction *RepeatTestWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::TestRepeat) {
            item = new RepeatTestAction();
        }
    RepeatTestAction *action = qobject_cast<RepeatTestAction *>(item);
    action->setRepeatTest(ui->rdRepeatTest->isChecked());
    action->setRecheckTest(ui->rdRecheckTest->isChecked());
    return action;
}

/******************************************************************/

} //namespace SDPO
