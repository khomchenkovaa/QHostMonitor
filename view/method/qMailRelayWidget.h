#ifndef QMAILRELAYWIDGET_H
#define QMAILRELAYWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class MailRelayWidget;
}

namespace SDPO {

class MailRelayWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit MailRelayWidget(QWidget *parent = 0);
    ~MailRelayWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void openPropertiesDlg();

private:
    Ui::MailRelayWidget *ui;
};

} // namespace SDPO

#endif // QMAILRELAYWIDGET_H
