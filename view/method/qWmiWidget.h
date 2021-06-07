#ifndef QWMIWIDGET_H
#define QWMIWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class WmiWidget;
}

namespace SDPO {

class WmiWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit WmiWidget(QWidget *parent = nullptr);
    ~WmiWidget();
    virtual void init(TestMethod *item = nullptr) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::WmiWidget *ui;
};

} // namespace SDPO

#endif // QWMIWIDGET_H
