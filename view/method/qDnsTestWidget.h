#ifndef QDNSTESTWIDGET_H
#define QDNSTESTWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class DnsTestWidget;
}

namespace SDPO {

class DnsTestWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit DnsTestWidget(QWidget *parent = 0);
    ~DnsTestWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::DnsTestWidget *ui;
};

} // namespace SDPO

#endif // QDNSTESTWIDGET_H
