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

private slots:
    void on_btnAdvanced_clicked();

    void on_btnProxy_clicked();

private:
    Ui::HttpWidget *ui;
};

} // namespace SDPO
#endif // QHTTPWIDGET_H
