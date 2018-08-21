#ifndef QSYSTEMLOGOPTIONSWIDGET_H
#define QSYSTEMLOGOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class SystemLogOptionsWidget;
}

namespace SDPO {

class SystemLogOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit SystemLogOptionsWidget(QWidget *parent = 0);
    ~SystemLogOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

    private slots:
        void on_btnSystemLogFileName_clicked();

private:
    Ui::SystemLogOptionsWidget *ui;
};

} // namespace SDPO

#endif // QSYSTEMLOGOPTIONSWIDGET_H
