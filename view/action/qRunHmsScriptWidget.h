#ifndef QRUNHMSSCRIPTWIDGET_H
#define QRUNHMSSCRIPTWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class RunHmsScriptWidget;
}

namespace SDPO {

class RunHmsScriptWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit RunHmsScriptWidget(QWidget *parent = 0);
    ~RunHmsScriptWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_toolButton_clicked();

private:
    Ui::RunHmsScriptWidget *ui;
};

} // namespace SDPO

#endif // QRUNHMSSCRIPTWIDGET_H
