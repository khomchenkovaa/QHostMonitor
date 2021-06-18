#ifndef QDOMINANTPROCESSWIDGET_H
#define QDOMINANTPROCESSWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class DominantProcessWidget;
}

namespace SDPO {

class DominantProcessWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit DominantProcessWidget(QWidget *parent = 0);
    ~DominantProcessWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::DominantProcessWidget *ui;
};

} // namespace SDPO

#endif // QDOMINANTPROCESSWIDGET_H
