#ifndef QMYSQLWIDGET_H
#define QMYSQLWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class MySqlWidget;
}

namespace SDPO {

class MySqlWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit MySqlWidget(QWidget *parent = 0);
    ~MySqlWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::MySqlWidget *ui;
};

} // namespace SDPO

#endif // QMYSQLWIDGET_H
