#ifndef QLOGPROCESSINGOPTIONSWIDGET_H
#define QLOGPROCESSINGOPTIONSWIDGET_H

#include "qOptionsWidget.h"


namespace Ui {
class LogProcessingOptionsWidget;
}

namespace SDPO {

class LogProcessingOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit LogProcessingOptionsWidget(QWidget *parent = 0);
    ~LogProcessingOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

    private slots:
        void on_chkLogsStatus();
        void on_SelectLogs();

private:
    Ui::LogProcessingOptionsWidget *ui;
};

} // namespace SDPO

#endif // QLOGPROCESSINGOPTIONSWIDGET_H
