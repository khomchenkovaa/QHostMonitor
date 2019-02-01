#ifndef QDNSTESTWIDGET_H
#define QDNSTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class DnsTestWidget;
}

namespace SDPO {

class DnsTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit DnsTestWidget(QWidget *parent = 0);
    ~DnsTestWidget();

    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::DnsTestWidget *ui;
};

} // namespace SDPO

#endif // QDNSTESTWIDGET_H
