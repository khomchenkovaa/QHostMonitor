#ifndef QPINGTRACEOPTIONSWIDGET_H
#define QPINGTRACEOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class PingTraceOptionsWidget;
}

namespace SDPO {

class PingTraceOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit PingTraceOptionsWidget(QWidget *parent = 0);
    ~PingTraceOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private:
    Ui::PingTraceOptionsWidget *ui;
};

} // namespace SDPO

#endif // QPINGTRACEOPTIONSWIDGET_H
