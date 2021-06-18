#ifndef QIMAPTESTWIDGET_H
#define QIMAPTESTWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class ImapTestWidget;
}

namespace SDPO {

class ImapTestWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit ImapTestWidget(QWidget *parent = 0);
    ~ImapTestWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
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
