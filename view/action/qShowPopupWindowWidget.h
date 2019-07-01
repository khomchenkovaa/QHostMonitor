#ifndef QSHOWPOPUPWINDOWWIDGET_H
#define QSHOWPOPUPWINDOWWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class ShowPopupWindowWidget;
}

namespace SDPO {

class ShowPopupWindowWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit ShowPopupWindowWidget(QWidget *parent = nullptr);
    ~ShowPopupWindowWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction* save(TestAction *item);

private slots:
    void on_btnPopupWindowSettings_clicked();

private:
    Ui::ShowPopupWindowWidget *ui;
};

} // namespace SDPO

#endif // QSHOWPOPUPWINDOWWIDGET_H
