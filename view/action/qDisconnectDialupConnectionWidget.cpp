#include "qDisconnectDialupConnectionWidget.h"
#include "ui_qDisconnectDialupConnectionWidget.h"
#include "action/tDisconnectDialupConnectionAction.h"

namespace SDPO {

/******************************************************************/

DisconnectDialupConnectionWidget::DisconnectDialupConnectionWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::DisconnectDialupConnectionWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

DisconnectDialupConnectionWidget::~DisconnectDialupConnectionWidget()
{
    delete ui;
}

/******************************************************************/

void DisconnectDialupConnectionWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::DialUpDisconnect) {
        return;
    }
    DisconnectDialupConnectionAction *action = qobject_cast<DisconnectDialupConnectionAction *>(item);
        ui->cmbDialupConnection->setCurrentText(action->getDialUpConnection());
}

/******************************************************************/

TestAction *DisconnectDialupConnectionWidget::save(TestAction *item)
{
     if (!item || item->getAction() != TActionID::DialUpDisconnect) {
                item = new DisconnectDialupConnectionAction();
            }
        DisconnectDialupConnectionAction *action = qobject_cast<DisconnectDialupConnectionAction *>(item);
        action->setDialUpConnection(ui->cmbDialupConnection->currentText());
        return action;
}

/******************************************************************/

} // namespace SDPO
