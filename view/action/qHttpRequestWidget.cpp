#include "qHttpRequestWidget.h"
#include "ui_qHttpRequestWidget.h"
#include "action/tHttpRequestAction.h"

namespace SDPO {

/******************************************************************/

HttpRequestWidget::HttpRequestWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::HttpRequestWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

HttpRequestWidget::~HttpRequestWidget()
{
    delete ui;
}

/******************************************************************/

void HttpRequestWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::HttpRequest) {
        return;
    }
    HttpRequestAction *action = qobject_cast<HttpRequestAction *>(item);
    ui->cmbHost->setCurrentText(action->getHost());
    ui->spinPort->setValue(action->getPort());
    ui->editRequest->setPlainText(action->getRequest());
}

/******************************************************************/

TestAction *HttpRequestWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::HttpRequest) {
        item = new HttpRequestAction();
    }
    HttpRequestAction *action = qobject_cast<HttpRequestAction *>(item);
    action->setHost(ui->cmbHost->currentText());
    action->setPort(ui->spinPort->value());
    action->setRequest(ui->editRequest->toPlainText());
    return action;
}

/******************************************************************/

} // namespace SDPO
