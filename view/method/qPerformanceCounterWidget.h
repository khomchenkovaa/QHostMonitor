#ifndef QPERFORMANCECOUNTERWIDGET_H
#define QPERFORMANCECOUNTERWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class PerformanceCounterWidget;
}

namespace SDPO {

class PerformanceCounterWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit PerformanceCounterWidget(QWidget *parent = 0);
    ~PerformanceCounterWidget();  
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::PerformanceCounterWidget *ui;
};

} // namespace SDPO
#endif // QPERFORMANCECOUNTERWIDGET_H
