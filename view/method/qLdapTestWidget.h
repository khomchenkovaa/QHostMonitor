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

private:
    Ui::LdapTestWidget *ui;
};

} // namespace SDPO

#endif // QLDAPTESTWIDGET_H
