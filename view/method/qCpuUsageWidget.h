#ifndef QCPUUSAGEWIDGET_H
#define QCPUUSAGEWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class CpuUsageWidget;
}

namespace SDPO {

class CpuUsageWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit CpuUsageWidget(QWidget *parent = 0);
    ~CpuUsageWidget();

    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_ComputerSelect();

private:
    Ui::CpuUsageWidget *ui;
};

} // namespace SDPO

#endif // QCPUUSAGEWIDGET_H
