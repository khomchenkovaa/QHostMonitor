#ifndef QHTTPREQUESTWIDGET_H
#define QHTTPREQUESTWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class HttpRequestWidget;
}

namespace SDPO {

class HttpRequestWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit HttpRequestWidget(QWidget *parent = 0);
    ~HttpRequestWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private:
    Ui::HttpRequestWidget *ui;
};

} // namespace SDPO

#endif // QHTTPREQUESTWIDGET_H
