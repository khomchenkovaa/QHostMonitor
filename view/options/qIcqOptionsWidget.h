#ifndef QICQOPTIONSWIDGET_H
#define QICQOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class IcqOptionsWidget;
}

namespace SDPO {

class IcqOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit IcqOptionsWidget(QWidget *parent = 0);
    ~IcqOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

    private slots:
        void on_btnIcqAccountsSwitch_clicked();

private:
    Ui::IcqOptionsWidget *ui;
};

} // namespace SDPO

#endif // QICQOPTIONSWIDGET_H
