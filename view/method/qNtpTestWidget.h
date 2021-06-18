#ifndef QNTPTESTWIDGET_H
#define QNTPTESTWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class NtpTestWidget;
}

namespace SDPO {

class NtpTestWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit NtpTestWidget(QWidget *parent = 0);
    ~NtpTestWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::NtpTestWidget *ui;
};

} // namespace SDPO
#endif // QNTPTESTWIDGET_H
