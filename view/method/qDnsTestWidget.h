#ifndef QDNSTESTWIDGET_H
#define QDNSTESTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class DnsTestWidget;
}

namespace SDPO {

class DnsTestWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit DnsTestWidget(QWidget *parent = 0);
    ~DnsTestWidget();

private:
    Ui::DnsTestWidget *ui;
};

} // namespace SDPO

#endif // QDNSTESTWIDGET_H
