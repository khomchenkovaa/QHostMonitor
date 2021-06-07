#ifndef QPOSTGRESQLWIDGET_H
#define QPOSTGRESQLWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class PostgreSqlWidget;
}

namespace SDPO {

class PostgreSqlWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit PostgreSqlWidget(QWidget *parent = 0);
    ~PostgreSqlWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::PostgreSqlWidget *ui;
};

} // namespace SDPO

#endif // QPOSTGRESQLWIDGET_H
