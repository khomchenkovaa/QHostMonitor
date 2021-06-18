#ifndef QCPUUSAGEWIDGET_H
#define QCPUUSAGEWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class CpuUsageWidget;
}

namespace SDPO {

class CpuUsageWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit CpuUsageWidget(QWidget *parent = 0);
    ~CpuUsageWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
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
