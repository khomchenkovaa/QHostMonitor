#ifndef QDRIVESPACEWIDGET_H
#define QDRIVESPACEWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class DriveSpaceWidget;
}

namespace SDPO {

class DriveSpaceWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit DriveSpaceWidget(QWidget *parent = 0);
    ~DriveSpaceWidget();

signals:

private:
    Ui::DriveSpaceWidget *ui;
};

} // namespace SDPO

#endif // QDRIVESPACEWIDGET_H
