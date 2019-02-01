#ifndef QIMAPTESTWIDGET_H
#define QIMAPTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class ImapTestWidget;
}

namespace SDPO {

class ImapTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit ImapTestWidget(QWidget *parent = 0);
    ~ImapTestWidget();

    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots :
    void checkMail_clicked();

private:
    Ui::ImapTestWidget *ui;
};

} // namespace SDPO

#endif // QIMAPTESTWIDGET_H
