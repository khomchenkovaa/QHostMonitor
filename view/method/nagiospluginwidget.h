#ifndef NAGIOSPLUGINWIDGET_H
#define NAGIOSPLUGINWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class NagiosPluginWidget;
}

namespace SDPO {

class NagiosPluginWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit NagiosPluginWidget(QWidget *parent = nullptr);
    ~NagiosPluginWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data=QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnSelect_clicked();
    void on_btnHelp_clicked();

private:
    Ui::NagiosPluginWidget *ui;
};

} // namespace SDPO

#endif // NAGIOSPLUGINWIDGET_H
