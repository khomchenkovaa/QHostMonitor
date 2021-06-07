#ifndef QLDAPTESTWIDGET_H
#define QLDAPTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class LdapTestWidget;
}

namespace SDPO {

class LdapTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit LdapTestWidget(QWidget *parent = 0);
    ~LdapTestWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots :
    void checkPerformSearch_clicked();

private:
    Ui::LdapTestWidget *ui;
};

} // namespace SDPO

#endif // QLDAPTESTWIDGET_H
