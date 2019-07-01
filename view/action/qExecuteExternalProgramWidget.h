#ifndef QEXECUTEEXTERNALPROGRAMWIDGET_H
#define QEXECUTEEXTERNALPROGRAMWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class ExecuteExternalProgramWidget;
}

namespace SDPO {

class ExecuteExternalProgramWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit ExecuteExternalProgramWidget(QWidget *parent = nullptr);
    ~ExecuteExternalProgramWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private:
    Ui::ExecuteExternalProgramWidget *ui;
};

} // namespace SDPO

#endif // QEXECUTEEXTERNALPROGRAMWIDGET_H
