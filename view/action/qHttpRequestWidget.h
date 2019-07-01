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
    explicit HttpRequestWidget(QWidget *parent = nullptr);
    ~HttpRequestWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private:
    Ui::HttpRequestWidget *ui;
};

} // namespace SDPO

#endif // QHTTPREQUESTWIDGET_H
