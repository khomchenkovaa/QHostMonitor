#ifndef QDICOMWIDGET_H
#define QDICOMWIDGET_H

#include "qTestWidget.h"
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QRadioButton>

namespace Ui {
class DicomWidget;
}

namespace SDPO {

class TTestMethod;

class DicomWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit DicomWidget(QWidget *parent = 0);
    ~DicomWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::DicomWidget *ui;
};

} // namespace SDPO

#endif // QDICOMWIDGET_H
