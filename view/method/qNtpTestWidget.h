#ifndef QNTPTESTWIDGET_H
#define QNTPTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class NtpTestWidget;
}

namespace SDPO {

class NtpTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit NtpTestWidget(QWidget *parent = 0);
    ~NtpTestWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::NtpTestWidget *ui;
};

} // namespace SDPO
#endif // QNTPTESTWIDGET_H
