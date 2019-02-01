#ifndef QORACLEWIDGET_H
#define QORACLEWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class OracleWidget;
}

namespace SDPO {

class OracleWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit OracleWidget(QWidget *parent = 0);
    ~OracleWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnTest_clicked();

private:
    Ui::OracleWidget *ui;

};

} // namespace SDPO

#endif // QORACLEWIDGET_H
