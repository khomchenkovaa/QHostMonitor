#ifndef QSQLQUERYWIDGET_H
#define QSQLQUERYWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SqlQueryWidget;
}

namespace SDPO {

class SqlQueryWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SqlQueryWidget(QWidget *parent = 0);
    ~SqlQueryWidget();

    virtual void init(TestAction *item = 0);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnSqlQuery_clicked();

private:
    Ui::SqlQueryWidget *ui;
};

} // namespace SDPO

#endif // QSQLQUERYWIDGET_H
