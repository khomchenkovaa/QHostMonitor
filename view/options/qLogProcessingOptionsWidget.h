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

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

    private slots:
        void on_chkLogsStatus();
        void on_SelectLogs();

private:
    Ui::LogProcessingOptionsWidget *ui;
};

} // namespace SDPO

#endif // QLOGPROCESSINGOPTIONSWIDGET_H
