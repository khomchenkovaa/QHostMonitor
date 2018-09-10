#ifndef QMSSQLWIDGET_H
#define QMSSQLWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class MsSqlWidget;
}

namespace SDPO {

class MsSqlWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit MsSqlWidget(QWidget *parent = 0);
    ~MsSqlWidget();

    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::MsSqlWidget *ui;
};

} // namespace SDPO

#endif // QMSSQLWIDGET_H
