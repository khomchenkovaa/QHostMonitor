#ifndef QPERFORMANCECOUNTERWIDGET_H
#define QPERFORMANCECOUNTERWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class PerformanceCounterWidget;
}

namespace SDPO {

class PerformanceCounterWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit PerformanceCounterWidget(QWidget *parent = 0);
    ~PerformanceCounterWidget();  
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::PerformanceCounterWidget *ui;
};

} // namespace SDPO
#endif // QPERFORMANCECOUNTERWIDGET_H
