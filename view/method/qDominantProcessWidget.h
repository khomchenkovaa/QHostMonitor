#ifndef QDOMINANTPROCESSWIDGET_H
#define QDOMINANTPROCESSWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class DominantProcessWidget;
}

namespace SDPO {

class DominantProcessWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit DominantProcessWidget(QWidget *parent = 0);
    ~DominantProcessWidget();

private:
    Ui::DominantProcessWidget *ui;
};

} // namespace SDPO

#endif // QDOMINANTPROCESSWIDGET_H
