#ifndef DIAGTESTWIDGET_H
#define DIAGTESTWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class DiagTestWidget;
}

namespace SDPO {

class DiagTestWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit DiagTestWidget(QWidget *parent = nullptr);
    ~DiagTestWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data=QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    void setupUI();

private slots:
    void onDataTypeChanged();
    void recalculateLimits();

private:
    Ui::DiagTestWidget *ui;
};

} // namespace SDPO

#endif // DIAGTESTWIDGET_H
