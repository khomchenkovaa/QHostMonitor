#ifndef QINTERBASEWIDGET_H
#define QINTERBASEWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class InterbaseWidget;
}

namespace SDPO {

class InterbaseWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit InterbaseWidget(QWidget *parent = 0);
    ~InterbaseWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::InterbaseWidget *ui;
};

} // namespace SDPO

#endif // QINTERBASEWIDGET_H
