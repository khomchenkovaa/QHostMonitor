#include "qShowPopupWindowWidget.h"
#include "ui_qShowPopupWindowWidget.h"
#include "qOptionsForm.h"
#include "action/tWinPopupAction.h"

namespace SDPO {

ShowPopupWindowWidget::ShowPopupWindowWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::ShowPopupWindowWidget)
{
    ui->setupUi(this);
}

ShowPopupWindowWidget::~ShowPopupWindowWidget()
{
    delete ui;
}

void ShowPopupWindowWidget::init(TestAction *item)
{
    Q_UNUSED(item)
}

TestAction *ShowPopupWindowWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::WinPopup) {
        item = new WinPopupAction();
    }
    return item;
}

void ShowPopupWindowWidget::on_btnPopupWindowSettings_clicked()
{
    OptionsForm dlg;
    dlg.setCurrentPage(13); // Msg Window
    dlg.exec();
}

} // namespace SDPO

