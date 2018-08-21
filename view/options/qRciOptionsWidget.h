#ifndef QRCIOPTIONSWIDGET_H
#define QRCIOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class RciOptionsWidget;
}

namespace SDPO {

class RciOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit RciOptionsWidget(QWidget *parent = 0);
    ~RciOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private slots:
        void on_checkedRemoteControle();

private:
    Ui::RciOptionsWidget *ui;
};

} // namespace SDPO

#endif // QRCIOPTIONSWIDGET_H
