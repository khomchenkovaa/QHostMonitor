#ifndef QDICOMWIDGET_H
#define QDICOMWIDGET_H

#include "testmethodwidget.h"
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QRadioButton>

namespace Ui {
class DicomWidget;
}

namespace SDPO {

class TestMethod;

class DicomWidget : public TestMethodWidget
{
    Q_OBJECT
public:
    explicit DicomWidget(QWidget *parent = 0);
    ~DicomWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::DicomWidget *ui;
};

} // namespace SDPO

#endif // QDICOMWIDGET_H
