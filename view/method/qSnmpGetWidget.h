#ifndef QSNMPGETWIDGET_H
#define QSNMPGETWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class SnmpGetWidget;
}

namespace SDPO {

class SnmpGetWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit SnmpGetWidget(QWidget *parent = nullptr);
    virtual ~SnmpGetWidget() Q_DECL_OVERRIDE;
    virtual void init(TestMethod *item = nullptr) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnSnmpCredentials_clicked();
    void on_btnMibBrowser_clicked();
    void on_btnGetValue_clicked();

private:
    Ui::SnmpGetWidget *ui;
};

} // namespace SDPO

#endif // QSNMPGETWIDGET_H
