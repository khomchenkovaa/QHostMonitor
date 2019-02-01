#ifndef QPINGWIDGET_H
#define QPINGWIDGET_H

#include "qTestWidget.h"
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QRadioButton>

namespace Ui {
class PingWidget;
}

namespace SDPO {

class TTestMethod;

class PingWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit PingWidget(QWidget *parent = 0);
    ~PingWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::PingWidget *ui;
};

} // namespace SDPO

#endif // QPINGWIDGET_H
