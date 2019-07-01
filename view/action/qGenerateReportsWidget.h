#ifndef QGENERATEREPORTSWIDGET_H
#define QGENERATEREPORTSWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class GenerateReportsWidget;
}

namespace SDPO {

class GenerateReportsWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit GenerateReportsWidget(QWidget *parent = nullptr);
    ~GenerateReportsWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_selectGenerateReports();

private:
    Ui::GenerateReportsWidget *ui;
};

} // namespace SDPO

#endif // QGENERATEREPORTSWIDGET_H
