#ifndef QSSHWIDGET_H
#define QSSHWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class SshWidget;
}

namespace SDPO {

class SshWidget : public TestMethodWidget
{
    Q_OBJECT
public:
    explicit SshWidget(QWidget *parent = nullptr);
    ~SshWidget() Q_DECL_OVERRIDE;

    virtual void init(TestMethod *item = nullptr) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private:
    Ui::SshWidget *ui;

};

} // namespace SDPO

#endif // QSSHWIDGET_H
