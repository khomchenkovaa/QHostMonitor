#ifndef QDHCPWIDGET_H
#define QDHCPWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class DhcpWidget;
}

namespace SDPO {

class DhcpWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit DhcpWidget(QWidget *parent = 0);
    ~DhcpWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
   // void IpValidator();

private:
    Ui::DhcpWidget *ui;
};

} // namespace SDPO

#endif // QDHCPWIDGET_H
