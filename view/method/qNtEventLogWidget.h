#ifndef QNTEVENTLOGWIDGET_H
#define QNTEVENTLOGWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class NtEventLogWidget;
}

namespace SDPO {

class NtEventLogWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit NtEventLogWidget(QWidget *parent = 0);
    ~NtEventLogWidget();

    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnLogSource_clicked();
    void on_btnAlertCondition_clicked();
    void on_btnConnectAs_clicked();

private:
    Ui::NtEventLogWidget *ui;

};

} // namespace SDPO

#endif // QNTEVENTLOGWIDGET_H
