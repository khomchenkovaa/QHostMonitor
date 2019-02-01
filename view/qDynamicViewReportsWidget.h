#ifndef QDYNAMICVIEWREPORTSWIDGET_H
#define QDYNAMICVIEWREPORTSWIDGET_H

#include <QWidget>

namespace Ui {
class DynamicViewReportsWidget;
}

namespace SDPO {

class DynamicViewReportsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DynamicViewReportsWidget(QWidget *parent = 0);
    ~DynamicViewReportsWidget();

private:
    Ui::DynamicViewReportsWidget *ui;
};

} // namespace SDPO

#endif // QDYNAMICVIEWREPORTSWIDGET_H
