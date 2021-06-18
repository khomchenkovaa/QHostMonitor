#ifndef QDRIVESPACEWIDGET_H
#define QDRIVESPACEWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class DriveSpaceWidget;
}

namespace SDPO {

class TestMethod;

class DriveSpaceWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit DriveSpaceWidget(QWidget *parent = 0);
    ~DriveSpaceWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::DriveSpaceWidget *ui;
};

} // namespace SDPO

#endif // QDRIVESPACEWIDGET_H
