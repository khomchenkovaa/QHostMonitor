#ifndef QHTTPWIDGET_H
#define QHTTPWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class HttpWidget;
}

namespace SDPO {

class HttpWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit HttpWidget(QWidget *parent = 0);
    ~HttpWidget();

    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnAdvanced_clicked();
    void on_btnProxy_clicked();

private:
    Ui::HttpWidget *ui;
};

} // namespace SDPO
#endif // QHTTPWIDGET_H
