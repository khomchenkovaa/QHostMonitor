#ifndef QPOP3TESTWIDGET_H
#define QPOP3TESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class Pop3TestWidget;
}

namespace SDPO {

class Pop3TestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit Pop3TestWidget(QWidget *parent = 0);
    ~Pop3TestWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::Pop3TestWidget *ui;
};

} // namespace SDPO

#endif // QPOP3TESTWIDGET_H
