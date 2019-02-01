#ifndef QSSHWIDGET_H
#define QSSHWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class SshWidget;
}

namespace SDPO {

class SshWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit SshWidget(QWidget *parent = 0);
    ~SshWidget();

signals:

private:
    Ui::SshWidget *ui;

};

} // namespace SDPO

#endif // QSSHWIDGET_H
