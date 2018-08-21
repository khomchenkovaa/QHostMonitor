#ifndef QDRIVESPACESIMPLEWIDGET_H
#define QDRIVESPACESIMPLEWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class DriveSpaceSimpleWidget;
}

namespace SDPO {

class TTestMethod;

class DriveSpaceSimpleWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit DriveSpaceSimpleWidget(QWidget *parent = 0);
    ~DriveSpaceSimpleWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::DriveSpaceSimpleWidget *ui;
};

} // namespace SDPO

#endif // QDRIVESPACESIMPLEWIDGET_H
