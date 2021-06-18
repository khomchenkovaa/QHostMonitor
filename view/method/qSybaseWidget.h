#ifndef QSYBASEWIDGET_H
#define QSYBASEWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class SybaseWidget;
}

namespace SDPO {

class SybaseWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit SybaseWidget(QWidget *parent = 0);
    ~SybaseWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::SybaseWidget *ui;
};

} // namespace SDPO

#endif // QSYBASEWIDGET_H
