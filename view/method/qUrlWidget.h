#ifndef QURLWIDGET_H
#define QURLWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class UrlWidget;
}

namespace SDPO {

class UrlWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit UrlWidget(QWidget *parent = 0);
    ~UrlWidget();

signals:

private slots:
    void on_btnUrl_clicked();
    void on_btnAdvanced_clicked();

private:
    Ui::UrlWidget *ui;
};

} // namespace SDPO

#endif // QURLWIDGET_H
