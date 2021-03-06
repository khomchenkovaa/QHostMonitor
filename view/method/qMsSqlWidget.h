#ifndef QMSSQLWIDGET_H
#define QMSSQLWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class MsSqlWidget;
}

namespace SDPO {

class MsSqlWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit MsSqlWidget(QWidget *parent = 0);
    ~MsSqlWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::MsSqlWidget *ui;
};

} // namespace SDPO

#endif // QMSSQLWIDGET_H
